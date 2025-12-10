import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required
# Lookup and USD removed, I won't use them.

# Configure application
app = Flask(__name__)

# app.jinja_env.filters["usd"] = usd; removed

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# First code change: we need to connect to the correct database.
db = SQL("sqlite:///habitos.db")


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
    # Original index deleted to create a completely new one.
    user_habits = db.execute("SELECT * FROM habits WHERE user_id = ?", session["user_id"]) #
    return render_template("index.html") # Python variables for HTML removed

@app.route("/add", methods=["GET", "POST"]) #as we are dealing with a form we need the POST route
@login_required # only with logged in user
def add():
    # If the user sent the form (POST)
    if request.method == "POST":
        habit = request.form.get("habit") # send habit to backend

        if not habit:
            return apology("you cannot send an empty habit") # if the habit was sent empty

        db.execute("INSERT INTO habits (user_id, name) VALUES (?, ?)", session["user_id"], habit) # sending the habit to the database, I had a small headache, INSERT was without R, INSET

        return redirect("/") # go to home page after create a new habit

    else:
        return render_template("add.html") # otherwise, if POST was not sent, we render the page.

# `@app.route buy` removed, completely useless.

# I've removed the `@app.route history` file; I'm going to create a new, completely different one.

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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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


# `@app.route quote` removed, also completely useless.


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        senha = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or not senha:
            return apology("empty username or password")
        if senha != confirmation:
            return apology("Your passwords don't match.")

        verificacao = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(verificacao) > 0:
            return apology("username already exists")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(senha))

        return redirect("/login")

    return render_template("register.html")



# `@app.route sell` removed, completely useless as well.
