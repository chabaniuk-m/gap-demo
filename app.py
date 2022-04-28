from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def main_page():
    return render_template("main_page.html")


@app.route("/solution_test", methods=['GET'])
def solution_test():
    return render_template("solution_test.html")
