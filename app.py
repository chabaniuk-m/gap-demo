from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/", methods=['GET'])
def main_page_get():
    return render_template("main_page.html")


@app.route("/solution_test", methods=['GET', 'POST'])
def solution_test_GET():
    if request.method == 'POST':
        print(request.form.get('polynom'))
    return render_template('solution_test.html')

