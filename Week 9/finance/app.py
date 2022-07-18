import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, user_shares_update

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        return redirect('/')
    else:
        rows = db.execute("SELECT * FROM users_shares WHERE user_id = ?", session['user_id'])
        for row in rows:
            quote = lookup(row['symbol'])
            row['price'] = quote['price']
            row['total_price'] = row['price'] * row['shares']
        return render_template("index.html", rows=rows)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":


        # Saving session id in variable
        id = session["user_id"]

        # Using lookup function to look for quote's info
        quote = lookup(request.form.get('symbol'))

        # Checking for errors
        if not id:
            return apology("An error occured. Please re-login", 403)

        # Checking if user's input is valid
        if not quote:
            return apology("Symbol doesn't exist", 403)

        # Saving values
        company_name = quote['name']
        symbol = quote['symbol']

        # Converting number of shares to int
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return redirect("/buy")

        # Making sure number of shares is a valid number
        if shares < 0:
            return apology("Buying negatives???-")

        # Saving variables
        unit_price = quote["price"]
        total_price = unit_price * shares


        rows = db.execute("SELECT * from users WHERE id = ?", id)

        if total_price > rows[0]["cash"]:
            return apology("not enough cash")

        # Insert purchase's data in database
        db.execute("INSERT INTO users_shares_history (user_id, company_name, symbol, num_shares, buy_sell, unity_price, total_price) VALUES(?, ?, ?, ?, ?, ?, ?)", id, company_name,symbol, shares, 'buy', unit_price, total_price)

        # Update money in account
        db.execute("UPDATE users SET cash = ? WHERE id = ?", rows[0]["cash"] - total_price, id)

        # Accesing the user shares summary
        rows = db.execute("SELECT * from users_shares where user_id = ? AND symbol = ?",id, symbol)

        # Checking if shares of tha symbol already exist in summary
        if len(rows) > 0:
            total_shares = int(rows[0]['shares'])
            total_value = int(rows[0]['total_value'])
        # If not create entry in table
        else:
            total_value = 0
            total_shares = 0
            db.execute('INSERT INTO users_shares (user_id, shares, company_name, symbol, total_value) VALUES (?, ?, ?, ?, ?)', id, total_shares, company_name, symbol, total_value)

        # Update table that contains shares summary
        db.execute("UPDATE users_shares SET shares = ?, total_value = ? WHERE user_id = ? AND symbol = ?", (total_shares + shares), (total_value + total_price), id, symbol)

        # return page with quote
        return render_template("bought.html", quote=quote, shares=shares)

    else:
        # return page to look up for quotes' info
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "POST":
        return redirect('/history')
    else:
        history = db.execute("SELECT * FROM users_shares_history WHERE user_id = ? ORDER BY timestamp DESC", session['user_id'])
        return render_template('history.html', history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Using lookup function to look for quote's info
        quote = lookup(request.form.get("symbol"))

        # Checking if user's input is valid
        if not quote:
            return apology("Symbol doesn't exist", 403)

        # return page with quote
        return render_template("quoted.html", quote=quote)

    else:
        # return page to look up for quotes' info
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("Must provide username", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check if username is available
        if username in rows or len(rows) > 0:
            return apology("Username already taken", 403)

        # Ensure password was submitted
        elif not password:
            return apology("Must provide password", 403)

        # Ensure password and confirmation nmatch
        elif confirmation != password:
            return apology("Password must match", 403)

        # Inserting new user into database
        rows = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
