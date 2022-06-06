from flask import Flask, request, render_template, url_for, escape

# create the Flask app
app = Flask(__name__)


@app.route('/')
def main_page():
    return render_template('main_page.html')


@app.route('/<number>.html', methods=['GET'])
def form_GET(number):
    print(escape(number))
    return render_template(f'{escape(number)}.html')


# При відправленні форми на сервер
# 1 рядок - номер задачі, всі рядки що далі - аргументи

# ГІВНОКОД!!!!!!!!
# номер задачі беру з номера шаблону (url), АЛЕ на одному шаблоні може бути 2-3 форми =(
@app.route('/<number>.html', methods=['POST'])
def form_POST(number):
    inputString = f'{escape(number)}'
    for value in request.form.to_dict().values():
        if value != "Розрахувати!":
            inputString += f'\n{value}'

    # Записую до input.txt
    f = open("input.txt", "w")
    f.write(inputString)  # Записує у тектовий документ
    f.close()

    # Читаю з output.txt
    f = open("output.txt")
    result = f.read()
    f.close()
    return render_template(f'{escape(number)}.html', result=result)


if __name__ == '__main__':
    # run app in debug mode on port 5000
    app.run(debug=True, port=5000)
