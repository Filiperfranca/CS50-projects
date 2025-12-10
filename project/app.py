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
    linhas = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

    portfolio = []
    grand_total = 0

    for linha in linhas:

        symbol = linha["symbol"]

        stock = lookup(symbol)

        valor_total = (stock["price"] * linha["total_shares"])

        grand_total += valor_total

        portfolio.append({
            "symbol": symbol,
            "name": stock["name"],
            "shares": linha["total_shares"],
            "price": stock["price"],
            "total": valor_total
        })

    user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    user_cash = user_cash_db[0]["cash"]

    grand_total += user_cash

    return render_template("index.html", stocks=portfolio, cash=user_cash, total=grand_total)


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("place a symbol")

        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid symbol")

        return render_template("quoted.html", quote=quote)

    return render_template("quote.html")


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



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_symbol = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        sharesStr = request.form.get("shares")

        if not symbol:
            return apology("place a symbol")
        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid symbol")

        if not sharesStr:
            return apology("choose a number of shares")
        try:
            shares = int(sharesStr)
            if shares <= 0:
                return apology("Your action number cannot be 0")
        except ValueError:
            return apology("Enter a valid value for the shares.")

        sharesUser = db.execute("SELECT SUM(shares) FROM transactions WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        shares_user = sharesUser[0]["SUM(shares)"]

        price = quote["price"]

        ganho = (price * shares)

        if shares_user < shares:
            return apology("Please don't try to scam us.")
        else:
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", ganho, session["user_id"])

            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, -shares, price)

        return redirect("/")

    return render_template("sell.html", symbols=user_symbol)
