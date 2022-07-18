-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Getting a general idea of the info I have been provided
.schema

-- Getting info from the crime reports
SELECT * FROM crime_scene_reports
WHERE street LIKE 'Humphrey Street';
-- Took place at 10:15. 7/28/2021

-- Let's check interviews now
SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;
-- Ruth says to check the bakery footage 10 minutes lapse.
-- The thief withdrew money from an atm at Legget Street.
-- Made a short call. Thief plans to take first plain tomorrow morning. The othe person on the phone will buy the fligh ticket

-- Checking bakery logs to see what happened in the 10 minute lapse when the crime ocurred
SELECT * FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28;
-- id 260 to 267

-- Checking withdrawals that day
SELECT * FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location LIKE 'Leggett Street';
-- Still to many suspects

-- Checking phone calls that last less than 1 minute
SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;
--

-- Checking first flight of 7/29/2021 based on the info a witness provided
SELECT * FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
ORDER BY hour;
-- first flight(id 36) goes to airport_id 4

-- Getting the city's name the thief escaped to
SELECT * FROM airports
WHERE id = 4;
-- New York City

-- Checking passengers from flight(id 36)
SELECT * FROM passengers
WHERE flight_id = 36;
--Reduced search to 8 passports

-- Comparing all the data that we've collected: Flight(id 36), account numbers from the atm transactions, license plates registered on bakery footage, and finally the suspicios phone numbers.
SELECT * FROM passengers
WHERE flight_id = 36
AND passport_number IN (SELECT passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street')
AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 14 AND minute < 24)
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60));
-- Thief passport found 5773159633

-- Looking at thief info to get his name and his accomplice info too
SELECT * FROM people
WHERE passport_number = 5773159633;
-- Thief is Bruce, phone number (367) 555-5533, passport 5773159633

-- Looking for his accomplice
SELECT * FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- Accomplice found. Name: Robert, phone number: (375) 555-8161, passport NUll