import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

month_length = 12
day_length = 31


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":
        # TODO: Add the user's entry into the database
        # Saves user's input
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        try:
           month_int = int(month)
           day_int = int(day)
        except ValueError:
            return redirect("/")

        # Checks for wrong forms
        if not name or month_int > month_length or not month or day_int > day_length or not day:
            return redirect("/")

        # INSERTS user's input into database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES ((?), (?) , (?))", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        # Saves the entries in the database on a variable
        birthdays = db.execute("SELECT * FROM birthdays")
        # Render template with database entries
        return render_template("index.html", birthdays=birthdays)


@app.route("/delete", methods=["GET", "POST"])
def delete():
    if request.method == "POST":
        id = request.form.get("id")
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
        return redirect("/")
    return redirect("/")


@app.route("/edit", methods=["GET", "POST"])
def edit():
    if request.method == "POST":
        id = request.form.get("id")
        entry = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
        return render_template("edit.html", entry=entry[0])

    return redirect("/")

@app.route("/editconfirm", methods=["GET", "POST"])
def editconfirm():
    if request.method == "POST":
        id = request.form.get("id")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        try:
           month_int = int(month)
           day_int = int(day)
        except ValueError:
            return redirect("/edit")

        # Checks for wrong forms
        if not name or month_int > month_length or not month or day_int > day_length or not day:
            return redirect("/edit")

        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id,)
        return redirect("/")

    return redirect("/")

