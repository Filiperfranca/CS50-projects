-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I use ".tables" to identify my work 'tools'.
.tables

-- I used ".schema crime_scene_reports". Understanding the crime scene is the best first step because it provides context and a direction to go from here.
.schema crime_scene_reports

-- I used "SELECT * FROM crime_scene_reports;" for an overview of the data, which makes it easier to refine the analysis later.
SELECT * FROM crime_scene_reports;

-- I used ".schema bakery_security_logs". After analyzing the crime scene data indicating the bakery, the only logical next step is to study the type of data stored in the bakery's security system to retrieve the data.
.schema bakery_security_logs

-- I used "SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour >= 10 AND hour < 11" to verify exactly everything the security system recorded at the bakery during the robbery.
SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour >= 10 AND hour < 11;

-- I used "SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour >= 9 AND hour < 11;" because I verified that someone left the bakery at 10:16 AM, one minute after the robbery, so I increased the time range to see what time the person entered.
SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour >= 9 AND hour < 11;

-- I used ".schema" to check all the tables and data types, to expand on what and where to work.
.schema

-- I used "SELECT * FROM people WHERE license_plate = '5P2BI95';" to check the main suspect because he was the only one who left the bakery at the time of the crime, and "SELECT * FROM people WHERE license_plate = '4328GD8';" because he entered accompanied by suspect 1.
SELECT * FROM people WHERE license_plate = '5P2BI95'; -- suspect 1
SELECT * FROM people WHERE license_plate = '4328GD8'; -- suspect 2 (accomplice)

-- I used "SELECT * FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;". Listening to what the interviews said will help separate what is false and clarify what is correct based on the data I obtained.
SELECT * FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;

-- I used "SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'". A witness said they saw the thief withdraw money earlier at the location of the code; let's start comparing the data.
SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'

-- I used "SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street');" to verify the account holders; one of them will be the thief. We will compare this with the license plates of the cars within the time frame given by the witness.
SELECT person_id FROM bank_accounts WHERE account_number IN  (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street');

-- I used "SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'));". Now we can verify that our suspect number 2 was in fact number 1, Luca, because he appears in the transaction and left at the same time the thief left the bakery, the only one. Let's look at the phone call.
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'));

-- I used "SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;". And again the tables turn, Diana, I hadn't quite realized it, she made the call, she made the transaction and left the bakery on time, she's the only one who matches perfectly.
SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

-- I used "SELECT * FROM airports WHERE city = 'Fiftyville';". to check airport id (8)
SELECT * FROM airports WHERE city = 'Fiftyville';

-- I used "SELECT * FROM flights WHERE year = 2024 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour, minute LIMIT 1;". With this, I can check the passengers and cross-reference the data again, taking the first flight of the day.
SELECT * FROM flights WHERE year = 2024 AND month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour, minute LIMIT 1;

-- I used "SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit') AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street')) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);". For final verification, and therefore avoiding human error, the machine returned the only person who left with the car at the time described by the witness, who completed the transaction, made the call, and was on the flight, and that person is: Bruce. (After judging so many times wrong, eventually we get it right)
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit') AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN  (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street')) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- I used "SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533");". and now, we have the person who helped Bruce in the robbery, the accomplice
SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533");

--I used "SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);". Finally, we retrieved the destination city of the flight Bruce took on the morning of the 29th using the destination ID from the flight ID.
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);
