from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

#routes and view functions for all the html pages

@app.route('/',methods=['GET'])
def home():
    return render_template("index.html")

if __name__ == '__main__':
    app.run(debug=True)