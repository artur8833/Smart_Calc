#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->result_show->setFocus();

  graph = new GraphWidget;
  connect(this, &MainWindow::signal, graph, &GraphWidget::slot);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_division, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_scale, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString new_lable = button->text();

  if (ui->result_show->hasFocus()) {
    if (ui->result_show->text() == "0") {
      ui->result_show->clear();
    }
    if ((new_lable == "sin") || (new_lable == "cos") || (new_lable == "acos") ||
        (new_lable == "asin") || (new_lable == "tan") ||
        (new_lable == "atan") || (new_lable == "log") || (new_lable == "ln") ||
        (new_lable == "sqrt")) {
      ui->result_show->setText(ui->result_show->text() + new_lable + "(");
    } else {
      ui->result_show->setText(ui->result_show->text() + new_lable);
    }
  } else if (ui->value_x->hasFocus()) {
    if (ui->value_x->text() == "0.0") {
      ui->value_x->clear();
    }
    ui->value_x->setText(ui->value_x->text() + new_lable);
  }
}

void MainWindow::on_pushButton_point_clicked() {
  ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::on_pushButton_ac_clicked() {
  if (ui->result_show->hasFocus()) {
    ui->result_show->clear();
    ui->result_show->setText("0");
  } else if (ui->value_x->hasFocus()) {
    ui->value_x->clear();
    ui->value_x->setText("0.0");
  }
}

void MainWindow::on_pushButton_del_clicked() {
  QString new_lable;

  if (ui->result_show->hasFocus()) {
    new_lable = ui->result_show->text();
  } else if (ui->value_x->hasFocus()) {
    new_lable = ui->value_x->text();
  }

  new_lable.chop(1);

  if ((new_lable.isEmpty()) && (ui->result_show->hasFocus())) {
    ui->result_show->setText("0");
  } else if (!(new_lable.isEmpty()) && (ui->result_show->hasFocus())) {
    ui->result_show->setText(new_lable);
  }

  if (((new_lable.isEmpty()) || (new_lable == "0.")) &&
      (ui->value_x->hasFocus())) {
    ui->value_x->setText("0.0");
  } else if (!(new_lable.isEmpty()) && (ui->value_x->hasFocus())) {
    ui->value_x->setText(new_lable);
  }
}

void MainWindow::on_pushButton_equals_clicked() {
  QString x_value = ui->value_x->text();
  double x = x_value.toDouble();

  QString display_value = ui->result_show->text();
  QByteArray value = display_value.toLocal8Bit();
  char *str = value.data();
  if (validation(str) == 1) {
    ui->result_show->setText("ERROR! INCORRECT EXPRESSION");
  } else {
    double result = 0;
    result = s21_calculator(str, x);
    QString str_res = QString::number(result, 'g', 16);
    ui->result_show->setText(str_res);
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  graph->show();
  double Xmin = ui->spinBox_x_min->text().toDouble();
  double Xmax = ui->spinBox_x_max->text().toDouble();
  double Ymin = ui->spinBox_y_min->text().toDouble();
  double Ymax = ui->spinBox_y_max->text().toDouble();
  QString display_value = ui->result_show->text();
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  emit signal(Xmin, Xmax, Ymin, Ymax, str);
}
