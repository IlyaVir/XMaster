#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <polynomial.h>
#include <fstream>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

std::ifstream fin;
std::ofstream fout;
std::ofstream logs;

struct list_polynomials {
    polynomial *polynomial_head;
    list_polynomials *next, *prev;
};

void print(list_polynomials *list) {
    if (list == nullptr) {
        std::cout << "void" << std::endl;
    }
    while (list != nullptr) {
        print(list -> polynomial_head);
        list = list -> next;
    }
}

std::string list_to_string(list_polynomials *list) {
    std::string ans;
    if (list == nullptr) {
        ans += "void";
    }
    while (list != nullptr) {
        ans += polynomial_to_string(list -> polynomial_head) + "\n";
        list = list -> next;
    }
    return ans;
}

list_polynomials *list_head = nullptr, *list_tail = nullptr;

int combo = 0;

QListWidgetItem *first = nullptr;

QMediaPlayer *voice = nullptr,
*ambient = nullptr,
*music = nullptr;

QMediaPlaylist *music_list = nullptr;

bool ai = true, am = true, mu = true;

polynomial *to_polynomial(std::string str) {
    if (!check_grammar(str)) {
        throw("Unknown error");
    } else {
        delete_spaces(str);
        return postfix_notation_to_polynomial(to_postfix_notation(str));
    }
}

polynomial *to_polynomial(QString qstr) {
    return to_polynomial(qstr.toStdString());
}

polynomial *solve_x(polynomial *head, polynomial *value) {
    polynomial *ans;
    ans = nullptr;

    std::string expression, polynomial_string = polynomial_to_string(value);
    while (head != nullptr) {
        expression += "(" + number_to_string(head -> coefficient) + ")*(" + polynomial_string + ")^(" + number_to_string(head -> power) + ")+";
        head = head -> next;
    }
    expression += "0";

    //std::cout << expression << std::endl;
    if (!expression.empty()) {
        ans = to_polynomial(expression);
    }

    return ans;
}

void pop(list_polynomials *&list) {
    if (list != nullptr) {
        list -> prev -> next = list -> next;
    }
    if (list -> next != nullptr) {
        list -> next -> prev = list -> prev;
    }
    delete_polynomial(list -> polynomial_head);
    delete list;
    list = nullptr;
}

void push_back(list_polynomials *&head, list_polynomials *&tail, polynomial *polynomial_head) {
    if (tail == nullptr) {
        head = tail = new list_polynomials;
        tail -> prev = nullptr;
        tail -> next = nullptr;
        tail -> polynomial_head = polynomial_head;
    } else {
        list_polynomials *new_list;
        new_list = new list_polynomials;
        new_list -> polynomial_head = polynomial_head;

        tail -> next = new_list;
        new_list -> prev = tail;
        new_list -> next = nullptr;
        tail = tail -> next;
    }
}

void delete_list(list_polynomials *&head, list_polynomials *&tail) {
    list_polynomials  *dead;
    while (head != nullptr) {
        dead = head;
        head = head -> next;

        delete_polynomial(dead -> polynomial_head);
        delete dead;
    }
    tail = nullptr;
}

void play(QMediaPlayer *&sound, QString path) {
    if (sound != nullptr) {
       sound -> stop();
       delete sound;
    }

    sound = new QMediaPlayer;
    sound -> setMedia(QUrl("qrc:/" + path));
    sound -> play();
}

void play(QMediaPlayer *&sound, QString path, bool may) {
    if (may) {
        play(sound, path);
    }
}

void stop(QMediaPlayer *&sound) {
    if (sound != nullptr) {
        sound -> stop();
        delete sound;
        sound = nullptr;
    }
}

void convert_from_file(QWidget *parent, list_polynomials *&head, list_polynomials *&tail) {
    head = tail = nullptr;
    std::string str, helper;
    while (std::getline(fin, str)) {
        try {
            push_back(head, tail, to_polynomial(str));
        } catch(...) {
            play(voice, "Sounds/Random.wav", ai);
            QMessageBox::warning(parent, "Беда", "<font size = 5>" + QString::fromStdString(str) + "<br>Этот ужас мы нашли в нашей Базе Данных. Либо вы лазили по ней, либо попытались внести туда опасное число нашей программой. Советуем больше не делать этого. Это сообщение может повторяться", "Я больше не буду");
            play(ambient, "Sounds/Change_3.wav", am);
            continue;
        }
    }
}

void convert_to_file(list_polynomials *head) {
    while (head != nullptr) {
        fout << polynomial_to_string(head -> polynomial_head) << '\n';
        head = head -> next;
    }
}

void convert_to_file(QListWidget *list) {
    for (int i = 0; i < list -> count(); ++i) {
        fout << list -> item(i) -> text().toStdString() << '\n';
    }
}

std::string qlist_to_string(QListWidget *list) {
    std::string ans;
    for (int i = 0; i < list -> count(); ++i) {
        ans += list -> item(i) -> text().toStdString() + '\n';
    }
    if (ans.empty()) {
        ans = "void\n";
    }
    return ans;
}

std::string qlist_selected_to_string(QListWidget *list) {
    std::string ans;
    for (int i = 0; i < list -> count(); ++i) {
        if (list -> item(i) -> isSelected()) {
            ans += list -> item(i) -> text().toStdString() + '\n';
        }
    }
    if (ans.empty()) {
        ans = "void\n";
    }
    return ans;
}

void refresh_list(QListWidget *to, list_polynomials *from) {
    first = nullptr;
    while (from != nullptr) {
        to -> addItem(QString::fromStdString(polynomial_to_string(from -> polynomial_head)));
        from = from -> next;
    }
}

void refresh_list_polynomials(QWidget *parent) {
    delete_list(list_head, list_tail);
    fin.open("data");
    if (fin.is_open()) {
        convert_from_file(parent, list_head, list_tail);
        fin.close();
    } else {
        play(voice, "Sounds/Where_is_it.wav", ai);
        QMessageBox::warning(parent, "Беда", "<font size = 5>УЖС!!!<br>База Данных пропала! Однако мы можем обойтись и без неё", "Я больше не буду удалять data");
        play(ambient, "Sounds/Change_3.wav", am);
    }
}

void save_settings() {
    fout.open("Settings");
    fout << ai << mu << am;
    fout.close();
}

void refresh_settings(QWidget *parent, QCheckBox *box_ai, QCheckBox *box_mu, QCheckBox *box_am) {
    fin.open("Settings");
    std::string str;
    if (fin.is_open()) {
        std::getline(fin, str);
        fin.close();

        if (str.size() < 3) {
            str = "111";
        }
    } else {
        play(voice, "Sounds/Where_is_it.wav", ai);
        QMessageBox::warning(parent, "Беда", "<font size = 5>УЖС!!!<br>Файл настроек пропал! Однако мы можем обойтись и без него", "Я больше не буду удалять Settings");
        play(ambient, "Sounds/Change_3.wav", am);
        str = "111";
        save_settings();
    }

    ai = str[0] - '0';
    mu = str[1] - '0';
    am = str[2] - '0';

    box_ai -> setChecked(ai);
    box_mu -> setChecked(mu);
    box_am -> setChecked(am);
}

void refresh_data() {
    fout.open("data");
    convert_to_file(list_head);
    fout.close();
}

void list_push_back(QWidget *parent, QListWidget *list, polynomial *elem) {
    push_back(list_head, list_tail, elem);
    refresh_data();
    refresh_list_polynomials(parent);
    list -> clear();
    refresh_list(list, list_head);
    first = nullptr;
}

bool to_ask(QWidget *parent, polynomial *head) {
    return QMessageBox::question(parent, "Зачем Вам это?", "<font size = 5>Сохранить?<br>" + QString::fromStdString(polynomial_to_string(head)) + "</font>",
                                 QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
}

bool to_ask(QWidget *parent, QString qstr) {
    return QMessageBox::question(parent, "Зачем Вам это?", "<font size = 5>Сохранить?<br>" + qstr + "</font>",
                                 QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
}

void add_log(QListWidget *parent, std::string action) {
    logs << action << "\nСостояние листа полиномов:\n" << list_to_string(list_head) << "\nСостояние WidgetList:\n" << qlist_to_string(parent) << "Выбраны в Widgetlist:\n" << qlist_selected_to_string(parent) << "-----------\n";
}

void refresh_app(QWidget *parent, QListWidget *list, QCheckBox *box_ai, QCheckBox *box_mu, QCheckBox *box_am) {
    refresh_settings(parent, box_ai, box_mu, box_am);
    refresh_list_polynomials(parent);
    refresh_list(list, list_head);
}

void init_music() {
    music_list = new QMediaPlaylist;

    music_list -> addMedia(QUrl("qrc:/Music/Classic.mp3"));
    music_list -> addMedia(QUrl("qrc:/Music/North.mp3"));
    music_list -> addMedia(QUrl("qrc:/Music/Horde.mp3"));
    music_list -> setCurrentIndex(1);
    music_list -> setPlaybackMode(QMediaPlaylist::Loop);

    if (mu) {
        music = new QMediaPlayer;
        music -> setPlaylist(music_list);
        music -> setVolume(50);
        music -> play();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XMaster");
    QWidget::setWindowIcon(QIcon("Title.ico"));


    refresh_app(parent, ui -> listWidget, ui -> checkBox, ui -> checkBox_2, ui -> checkBox_3);
    init_music();
    logs.open("logs.txt");
    add_log(ui -> listWidget, "Старт программы\n");

}

MainWindow::~MainWindow()
{
    logs.close();
    delete ui;
}

void error_sound(QPushButton *Button, int code) {
    play(ambient, "Sounds/Impossible.wav", am);

    if (++combo >= 8) {
        combo = 0;
        play(voice, "Sounds/A_lot_of_errors.wav", ai);
        Button -> setEnabled(true && ai);
    } else if (code == 0) {
        play(voice, "Sounds/It_is_not_easy_(float_or_x_in_pow).wav", ai);
    } else if (code == 1) {
        play(voice, "Sounds/Is_it_possible.wav", ai);
    } else if (code == 2) {
        play(voice, "Sounds/Error.wav", ai);
    }
}

void clear_first() {
    try {
        if (first != nullptr) {
            first -> setBackgroundColor(QColor(0, 0, 0, 0));
            first = nullptr;
        }
    } catch(...) {
        //continue
    }
}

void clear_selected(QListWidget *list) {
    clear_first();
    if (list -> selectedItems().size() > 0) {
        for (int i = list -> selectedItems().size() - 1; i >= 0; --i) {
            list -> selectedItems()[i] -> setSelected(false);
        }
    }
}

void is_it_save(QWidget *parent, QListWidget *list, polynomial *new_polynomial) {
    play(ambient, "Sounds/Change_3.wav", am);

    combo = 0;
    play(voice, "Sounds/Are_you_know_why.wav", ai);
    if (to_ask(parent, new_polynomial)) {
        list_push_back(parent, list, new_polynomial);

        play(ambient, "Sounds/Change_2.wav", am);
    } else {
        play(ambient, "Sounds/Change_3.wav", am);
        delete_polynomial(new_polynomial);
    }
}

void is_it_save(QWidget *parent, QListWidget *list, polynomial *new_polynomial, QString qstr) {
    play(ambient, "Sounds/Change_3.wav", am);

    combo = 0;
    play(voice, "Sounds/Are_you_know_why.wav", ai);
    if (to_ask(parent, qstr)) {
        list_push_back(parent, list, new_polynomial);

        play(ambient, "Sounds/Change_2.wav", am);
    } else {
        play(ambient, "Sounds/Change_3.wav", am);
        delete_polynomial(new_polynomial);
    }
}

void MainWindow::on_pushButton_10_clicked() // Ввод
{
    QString qstr_polynomial = ui -> input -> text();
    add_log(ui -> listWidget, "Ввели " + qstr_polynomial.toStdString() + "\n");
    polynomial *head;
    try {
        try {
            head = to_polynomial(qstr_polynomial);
            play(ambient, "Sounds/Change_3.wav", am);

            is_it_save(this, ui -> listWidget, head, qstr_polynomial + " = " +  QString::fromStdString(polynomial_to_string(head)));
            play(voice, "Sounds/Harder.wav", ai);

            clear_selected(ui -> listWidget);
            ui -> input -> clear();
            combo = 0;
            add_log(ui -> listWidget, "Успешно распознано\n");
        } catch(std::pair <int, std::string> error) {
            error_sound(ui -> pushButton_13, error.first);
            QMessageBox::critical(this, "Error 404", "<font size = 5>" + qstr_polynomial + "<br>" + QString::fromStdString(error.second) + "</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        } catch(error err) {
            error_sound(ui -> pushButton_13, err.code);

            //std::string qtext = "<font size = 5>", str_polynomial = qstr_polynomial.toStdString();
            QString qtext = "<font size = 5>";
            for (int i = 0; i < qstr_polynomial.size(); ++i) {
                if (i == err.pos) {
                    qtext += "</font><b><font size = 6>";
                    qtext += qstr_polynomial[i];
                    qtext += "</font></b><font size = 5>";
                } else {
                    qtext += qstr_polynomial[i];
                }
            }
            if (qstr_polynomial.size() < err.pos + 1) {
                qtext += "<b><font size = 6>?</font></b>";
            }
            qtext += "</font><br>";

            QMessageBox::critical(this, "Error 404", qtext + "<font size = 5>" + QString::fromStdString(err.text) + "</font>", "Я больше не буду так делать");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    } catch (...) {
        play(ambient, "Sounds/Impossible.wav", am);

        if (++combo >= 8) {
            combo = 0;
            play(voice, "Sounds/A_lot_of_errors.wav", ai);
            ui -> pushButton_13 -> setEnabled(true && ai);
        } else {
            play(voice, "Sounds/Why.wav", ai);
        }
        if (qstr_polynomial.size() == 0) {
            QMessageBox::critical(this, "Error 404", "<font size = 5>Пустая строка. Какой в этом смысл?</font>", "Я исправлюсь");
        } else {
            QMessageBox::critical(this, "Error 404", "<font size = 5>Только пробелы. Какой в этом смысл?</font>", "Я исправлюсь");
        }
        play(ambient, "Sounds/Change_3.wav", am);
        play(voice, "Sounds/Tell_me.wav", ai);
    }
}

void MainWindow::on_checkBox_2_clicked() // Music
{
    play(ambient, "Sounds/Change_3.wav", am);
    if (!mu) {
        if (music == nullptr) {
            music = new QMediaPlayer;
            music -> setPlaylist(music_list);
            music -> setVolume(50);
        }
        music -> play();
        add_log(ui -> listWidget, "Включили музыку\n");
    } else {
        add_log(ui -> listWidget, "Остановили музыку\n");
        music -> pause();
    }
    mu = !mu;
    save_settings();
}

void MainWindow::on_checkBox_clicked() // ai
{
    play(ambient, "Sounds/Change_3.wav", am);
    if (ai) {
        add_log(ui -> listWidget, "Выключили ИИ\n");
        stop(voice);
        ui -> pushButton_13 -> setEnabled(false);
    } else {
       add_log(ui -> listWidget, "Включили ИИ\n");
    }
    ai = !ai;
    save_settings();
}

void MainWindow::on_checkBox_3_clicked()
{
    if (am) {
        stop(ambient);
        add_log(ui -> listWidget, "Выключили звук клавиш\n");
    } else {
        add_log(ui -> listWidget, "Включили звук клавиш\n");
    }
    am = !am;
    play(ambient, "Sounds/Change_3.wav", am);
    save_settings();
}

void MainWindow::on_input_returnPressed()
{
    on_pushButton_10_clicked();
}

void MainWindow::on_listWidget_clicked() // click
{
    //std::cout << ui -> listWidget -> selectedItems().size() << std::endl;
    add_log(ui -> listWidget, "Тыкнули в листе\n");

    clear_first();
    if (ui -> listWidget -> selectedItems().size() > 0) {
        first = ui -> listWidget -> selectedItems()[ui -> listWidget -> selectedItems().size() - 1];
        first -> setBackgroundColor(QColor(255, 255, 0, 255));
    }

    if (ui -> listWidget -> selectedItems().size() == 2) {
        play(voice, "Sounds/Begin_faster.wav", ai);
    }
}

void standard_react(QPushButton *Button) {
    play(ambient, "Sounds/Impossible.wav", am);
    if (++combo >= 8) {
        play(voice, "Sounds/A_lot_of_errors.wav", ai);
        combo = 0;
        Button -> setEnabled(ai);
    } else {
        play(voice, "Sounds/It_is_not_easy_(float_or_x_in_pow).wav", ai);
    }
}

QString list_to_qstr(list_polynomials *head) {
    QString qstr;
    if (head != nullptr) {
        qstr += QString::fromStdString(polynomial_to_string(head -> polynomial_head));
        head = head -> next;
    }
    while (head != nullptr) {
        qstr += "<br>" + QString::fromStdString(polynomial_to_string(head -> polynomial_head));
        head = head -> next;
    }
    return qstr;
}

void list_to_global_list(QWidget *parent, QListWidget *list, list_polynomials *&head) {
    while (head != nullptr) {
        list_push_back(parent, list, head -> polynomial_head);
        head = head -> next;
    }
    play(ambient, "Sounds/Change_2.wav", am);
}

void is_its_save(QWidget *parent, QListWidget *list, list_polynomials *&head, list_polynomials *&tail) {
    play(ambient, "Sounds/Change_3.wav", am);

    QString qstr = list_to_qstr(head);
    combo = 0;
    play(voice, "Sounds/Are_you_know_why.wav", ai);
    if (to_ask(parent, qstr)) {
        list_to_global_list(parent, list, head);
    } else {
        play(ambient, "Sounds/Change_3.wav", am);
        delete_list(head, tail);
    }
}

void is_its_save(QWidget *parent, QListWidget *list, list_polynomials *&head, list_polynomials *&tail, QString qstr) {
    play(ambient, "Sounds/Change_3.wav", am);

    combo = 0;
    play(voice, "Sounds/Are_you_know_why.wav", ai);
    if (to_ask(parent, qstr)) {
        list_to_global_list(parent, list, head);
    } else {
        play(ambient, "Sounds/Change_3.wav", am);
        delete_list(head, tail);
    }
}

void MainWindow::on_pushButton_clicked() // +
{
    add_log(ui -> listWidget, "Cкладывают полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для сложения нужно выбрать хотя бы 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr;

            polynomial *ans;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size(); ++i) {
                if (i != 0) {
                    qstr += " + ";
                }
                qstr += '(' + ui -> listWidget -> selectedItems()[i] -> text() + ')';
            }
            ans = to_polynomial(qstr);

            is_it_save(this, ui -> listWidget, ans, qstr + " = " + QString::fromStdString(polynomial_to_string(ans)));
            add_log(ui -> listWidget, "Успешно складывают\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_2_clicked() // -
{
    add_log(ui -> listWidget, "Вычитают полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для вычитания нужно выбрать хотя бы 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr = '(' + ui -> listWidget -> selectedItems()[ui -> listWidget -> selectedItems().size() - 1] -> text() + ')';

            polynomial *ans;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size() - 1; ++i) {
                qstr += " - (" + ui -> listWidget -> selectedItems()[i] -> text() + ')';
            }
            ans = to_polynomial(qstr);

            is_it_save(this, ui -> listWidget, ans, qstr + " = " + QString::fromStdString(polynomial_to_string(ans)));
            add_log(ui -> listWidget, "Успешно вычитают\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
    play(ambient, "Sounds/Change_3.wav", am);
}

void MainWindow::on_pushButton_3_clicked() // *
{
    add_log(ui -> listWidget, "Умножают полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для умножения нужно выбрать хотя бы 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr;

            polynomial *ans;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size(); ++i) {
                if (i != 0) {
                    qstr += " * ";
                }
                qstr += '(' + ui -> listWidget -> selectedItems()[i] -> text() + ')';
            }
            ans = to_polynomial(qstr);

            is_it_save(this, ui -> listWidget, ans, qstr + " = " + QString::fromStdString(polynomial_to_string(ans)));
            add_log(ui -> listWidget, "Успешно умножают\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_9_clicked() // ==
{
    add_log(ui -> listWidget, "Сравнивают полиномы\n");
    if (ui -> listWidget -> selectedItems().size() != 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для сравнения нужно выбрать только 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            polynomial *new_polynomial, *tmp_polynomial;
            new_polynomial = to_polynomial(ui -> listWidget -> selectedItems()[0] -> text());
            tmp_polynomial = to_polynomial(ui -> listWidget -> selectedItems()[1] -> text());
            play(ambient, "Sounds/Change_3.wav", am);

            if (equal(new_polynomial, tmp_polynomial)) {
                QMessageBox::information(this, "Вердикт", "Они равны", "Согласен");
            } else {
                QMessageBox::information(this, "Вердикт", "Они не равны", "Согласен");
            }
            play(ambient, "Sounds/Change_3.wav", am);

            delete_polynomial(new_polynomial);
            delete_polynomial(tmp_polynomial);

            combo = 0;
            clear_selected(ui -> listWidget);
            add_log(ui -> listWidget, "Успешно сравнивают\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_13_clicked() // Усмирить ИИ
{
    add_log(ui -> listWidget, "Конфликтуют с ИИ\n");

    play(ambient, "Sounds/Impossible.wav", am);
    play(voice, "Sounds/Hush.mp3", ai);
    QMessageBox::warning(this, "Предупреждение", "ИИ сопротивляется", "Попытаться задавить его своей мощью");

    play(ambient, "Sounds/Impossible.wav", am);
    play(voice, "Sounds/Your_death.wav", ai);
    QMessageBox::critical(this, "Опасность", "Вы смогли взбесить ИИ. Молите о пощаде", "Молить о пощаде");

    play(ambient, "Sounds/Change_3.wav", am);
    play(voice, "Sounds/Try_again.wav", ai);
    QMessageBox::information(this, "Объяснение", "Вам повезло - ИИ простил Вас", "Радоваться чудесному спасению");
    play(ambient, "Sounds/Change_3.wav", am);
    combo = 0;
    ui -> pushButton_13 -> setEnabled(false);
    add_log(ui -> listWidget, "Успешно избегают незавидной участи\n");
}

void MainWindow::on_pushButton_4_clicked() // div
{
    add_log(ui -> listWidget, "Делят полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для целочисленного деления нужно выбрать хотя бы 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString dividable = '(' + ui -> listWidget -> selectedItems()[ui -> listWidget -> selectedItems().size() - 1] -> text() + ')',
                    divider;

            polynomial *ans, *p_divable, *p_divider;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size() - 1; ++i) {
                if (i != 0) {
                    divider += " * ";
                }
                divider += '(' + ui -> listWidget -> selectedItems()[i] -> text() + ')';


            }
            p_divable = to_polynomial(dividable);
            p_divider = to_polynomial(divider);
            std::pair <polynomial*, polynomial*> div_mod = division_polynomials(p_divable, p_divider);
            delete_polynomial(div_mod.second);
            ans = div_mod.first;

            is_it_save(this, ui -> listWidget, ans, dividable + " / (" + divider + ") = " + QString::fromStdString(polynomial_to_string(ans)));
            add_log(ui -> listWidget, "Успешно делят\n");
        } catch(std::pair <int, std::string> err) {
            standard_react(ui -> pushButton_13);
            error_sound(ui -> pushButton_13, err.first);
            QMessageBox::critical(this, "Error 404", "<font size = 5>" + QString::fromStdString(err.second) + "</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_8_clicked() // %
{
    add_log(ui -> listWidget, "Смотрят остатки полиномов\n");
    if (ui -> listWidget -> selectedItems().size() < 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для просмотра остатка нужно выбрать хотя бы 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString dividable = '(' + ui -> listWidget -> selectedItems()[ui -> listWidget -> selectedItems().size() - 1] -> text() + ')',
                    divider;

            polynomial *ans, *p_divable, *p_divider;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size() - 1; ++i) {
                if (i != 0) {
                    divider += " * ";
                }
                divider += '(' + ui -> listWidget -> selectedItems()[i] -> text() + ')';


            }
            p_divable = to_polynomial(dividable);
            p_divider = to_polynomial(divider);
            std::pair <polynomial*, polynomial*> div_mod = division_polynomials(p_divable, p_divider);
            delete_polynomial(div_mod.first);
            ans = div_mod.second;

            is_it_save(this, ui -> listWidget, ans, dividable + " % (" + divider + ") = " + QString::fromStdString(polynomial_to_string(ans)));
            add_log(ui -> listWidget, "Успешно смотрят остатки\n");
        } catch(std::pair <int, std::string> err) {
            standard_react(ui -> pushButton_13);
            error_sound(ui -> pushButton_13, err.first);
            QMessageBox::critical(this, "Error 404", "<font size = 5>" + QString::fromStdString(err.second) + "</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_5_clicked() // f'(x)
{
    add_log(ui -> listWidget, "Берут производную\n");
    if (ui -> listWidget -> selectedItems().size() < 1) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для взятия производной нужно выбрать хотя бы 1 элемент</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr;

            list_polynomials *head, *tail;
            head = tail = nullptr;
            polynomial *tmp_polynomial;
            tmp_polynomial = nullptr;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size(); ++i) {
                tmp_polynomial = to_polynomial(ui -> listWidget -> selectedItems()[i] -> text());
                push_back(head, tail, find_derivative(tmp_polynomial));
                if (i != 0) {
                    qstr += "<br>";
                }
                qstr += '(' + ui -> listWidget -> selectedItems()[i] -> text() + ")' = " + QString::fromStdString(polynomial_to_string(tail -> polynomial_head));

                delete_polynomial(tmp_polynomial);
            }

            is_its_save(this, ui -> listWidget, head, tail, qstr);
            add_log(ui -> listWidget, "Успешно берут производную\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_11_clicked() // copy
{
    add_log(ui -> listWidget, "Копируют полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 1) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для копирования нужно выбрать хотя бы 1 элемент</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            list_polynomials *head, *tail;
            head = tail = nullptr;

            for (int i = 0; i < ui -> listWidget -> selectedItems().size(); ++i) {
                push_back(head, tail, to_polynomial(ui -> listWidget -> selectedItems()[i] -> text()));
            }

            play(ambient, "Sounds/Change_3.wav", am);

            QString qstr = list_to_qstr(head);
            combo = 0;

            list_to_global_list(this, ui -> listWidget, head);
            QMessageBox::information(this, "Статус", "<font size = 5>" + qstr + "<br>Успешно скопировано</font>");
            play(ambient, "Sounds/Change_3.wav", am);

            add_log(ui -> listWidget, "Успешно копируют\n");
        } catch(...) {
            play(ambient, "Sounds/Impossible.wav", am);
            play(voice, "Randow.wav", ai);
            QMessageBox::critical(this, "Error 404", "<font size = 5>У меня почему-то не получается это скопировать</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_12_clicked() // delete
{
    add_log(ui -> listWidget, "Удаляют полиномы\n");
    if (ui -> listWidget -> selectedItems().size() < 1) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для удаления нужно выбрать хотя бы 1 элемент</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr = "";
            for (int i = ui -> listWidget -> count() - 1; i >= 0; --i) {
                if (ui -> listWidget -> item(i) -> isSelected()) {
                    if (qstr.size() != 0) {
                        qstr += "<br>";
                    }
                    qstr += ui -> listWidget -> item(i) -> text();
                    delete ui -> listWidget -> item(i);

                }
            }
            fout.open("data");
            convert_to_file(ui -> listWidget);
            fout.close();
            first = nullptr;
            refresh_list_polynomials(this);

            QMessageBox::information(this, "Статус" ,"<font size = 5>" + qstr + "<br>Успешно удалено</font>");
            combo = 0;

            play(ambient, "Sounds/Change_1.wav", am);
            add_log(ui -> listWidget, "Успешно удаляют\n");
        } catch(...) {
            play(ambient, "Sounds/Impossible.wav", am);
            play(voice, "Randow.wav", ai);
            QMessageBox::critical(this, "Error 404", "<font size = 5>У меня почему-то не получается это удалить</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_6_clicked() // f(x)
{
    add_log(ui -> listWidget, "Вычисляют значение функции\n");
    if (ui -> listWidget -> selectedItems().size() != 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для вычисления значения функции нужно выбрать только 2 элемента - функцию и значение её аргумента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            polynomial *new_polynomial, *tmp_polynomial, *ans;
            new_polynomial = to_polynomial(ui -> listWidget -> selectedItems()[1] -> text());
            tmp_polynomial = to_polynomial(ui -> listWidget -> selectedItems()[0] -> text());
            play(ambient, "Sounds/Change_3.wav", am);

            ans = solve_x(new_polynomial, tmp_polynomial);

            is_it_save(this, ui -> listWidget, ans, "f(" + QString::fromStdString(polynomial_to_string(tmp_polynomial)) + ") = " + QString::fromStdString(polynomial_to_string(ans)));

            delete_polynomial(new_polynomial);
            delete_polynomial(tmp_polynomial);

            add_log(ui -> listWidget, "Успешно вычисляют\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}

void MainWindow::on_pushButton_7_clicked() // int solves
{
    add_log(ui -> listWidget, "Ищут целые корни\n");
    if (ui -> listWidget -> selectedItems().size() != 1) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для нахождения целочисленных корней функции нужно выбрать только 1 элемент</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            play(ambient, "Sounds/Change_3.wav", am);
            polynomial *tmp_head;
            tmp_head = to_polynomial(ui -> listWidget -> selectedItems()[0] -> text());

            if (tmp_head == nullptr || tmp_head -> power == 0) {
                if (tmp_head == nullptr) {
                    QMessageBox::information(this, "О чудо!", "У этого полинома бесконечное количество корней", "Воистину");
                } else {
                    QMessageBox::information(this, "О чудо!", "У этого полинома вообще нет корней", "Воистину");
                }
                play(ambient, "Sounds/Change_3.wav", am);
                clear_selected(ui -> listWidget);
            } else {
                list_polynomials *head, *tail;
                head = tail = nullptr;

                polynomial *free, *value, *polynomial_x;
                free = tmp_head;
                while (free -> next != nullptr) {
                    free = free -> next;
                }
                //std::cout << free ->coefficient << std::endl;
                for (long long x = 0; x <= std::abs(free -> coefficient); ++x) {
                    //std::cout << "x = " << x << std::endl;
                    try {
                        polynomial_x = create_x(x, 0);
                        value = solve_x(tmp_head, polynomial_x);

                        if (value == nullptr) {
                            push_back(head, tail, polynomial_x);
                        } else {
                            delete_polynomial(polynomial_x);
                        }
                        delete_polynomial(value);

                        if (x != 0) {
                            polynomial_x = create_x(-x, 0);
                            value = solve_x(tmp_head, polynomial_x);


                            if (value == nullptr) {
                                push_back(head, tail, polynomial_x);
                            } else {
                                delete_polynomial(polynomial_x);
                            }
                            delete_polynomial(value);
                        }

                    } catch(...) {
                        break;
                    }
                }

                if (head == nullptr) {
                    QMessageBox::information(this, "УЖС", "У этого полинома нет целочисленных корней", "Я в печали");
                    play(ambient, "Sounds/Change_3.wav", am);
                    clear_selected(ui -> listWidget);
                } else {
                    print(head);
                    is_its_save(this, ui -> listWidget, head, tail);
                }
            }

            add_log(ui -> listWidget, "Успешно находят\n");
        } catch(...) {
            standard_react(ui -> pushButton_13);
            QMessageBox::critical(this, "Error 404", "<font size = 5>Вы лезли в длинную арифметику и раньше. Пожалуйста, не надо этого больше делать. Это всё.</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
    on_listWidget_clicked();
}

void MainWindow::on_pushButton_14_clicked() // select all
{
    add_log(ui -> listWidget, "Выделяют всё");
    clear_selected(ui -> listWidget);
    ui -> listWidget -> selectAll();
    if (ui -> listWidget -> selectedItems().size() > 0) {
        first = ui -> listWidget -> selectedItems()[ui -> listWidget -> selectedItems().size() - 1];
        on_listWidget_clicked();
    }
    play(ambient, "Sounds/Change_3.wav", am);
    add_log(ui -> listWidget, "Успешно выделяют");
}

void MainWindow::on_pushButton_15_clicked()
{
    add_log(ui -> listWidget, "Снимают всё");
    clear_selected(ui -> listWidget);
    play(ambient, "Sounds/Change_3.wav", am);
    add_log(ui -> listWidget, "Успешно снимают");
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    on_listWidget_clicked();
}

void MainWindow::on_pushButton_16_clicked() // ^
{
    add_log(ui -> listWidget, "Возводят в степень\n");
    if (ui -> listWidget -> selectedItems().size() != 2) {
        standard_react(ui -> pushButton_13);
        QMessageBox::warning(this, "Error 404", "<font size = 5>Для возведения в степень нужно только 2 элемента</font>");
        play(ambient, "Sounds/Change_3.wav", am);
    } else {
        try {
            QString qstr = '(' + ui -> listWidget -> selectedItems()[1] -> text() + ") ^ (" + ui -> listWidget -> selectedItems()[0] -> text() + ')';

            polynomial *ans;
            ans = to_polynomial(qstr);

            is_it_save(this, ui -> listWidget, ans, qstr + " = " + QString::fromStdString(polynomial_to_string(ans)));

            add_log(ui -> listWidget, "Успешно возводят\n");
        }  catch(std::pair <int, std::string> error) {
            error_sound(ui -> pushButton_13, error.first);
            QMessageBox::critical(this, "Error 404", "<font size = 5>" + QString::fromStdString(error.second) + "</font>");
            play(ambient, "Sounds/Change_3.wav", am);
        }
    }
}
