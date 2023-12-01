# pip install Flask-Mail

from flask import Flask, request, render_template, redirect, url_for
from flask_mail import Mail, Message

app = Flask(__name__)

app.config['MAIL_SERVER'] = 'smtp.gmail.com'
app.config['MAIL_PORT'] = 587
app.config['MAIL_USERNAME'] = 'vinit2004mehtaa@gmail.com'
app.config['MAIL_PASSWORD'] = ''
app.config['MAIL_USE_TLS'] = True
app.config['MAIL_USE_SSL'] = False
app.config['MAIL_DEFAULT_SENDER'] = 'vinit2004mehtaa@gmail.com'

mail = Mail(app)


#routes and view functions for all the html pages

@app.route('/',methods=['GET'])
def home():
    return render_template("index.html")

@app.route('/contact', methods=['GET', 'POST'])
def contact():
    if request.method == 'POST':
        name = request.form['name']
        email = request.form['email']
        subject = request.form['subject']
        message = request.form['message']

        # Create and send the email using Flask-Mail
        msg = Message(subject, recipients=['recipient@example.com'])
        msg.body = f"Name: {name}\nEmail: {email}\nSubject: {subject}\nMessage: {message}"
        mail.send(msg)
        
        return render_template('index.html')



if __name__ == '__main__':
    app.run(debug=True)