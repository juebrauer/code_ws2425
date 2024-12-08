#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

class CounterWidget : public QWidget {
    Q_OBJECT

public:
    CounterWidget(QWidget *parent = nullptr) : QWidget(parent), counter(0) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Initialize label
        label = new QLabel("Counter: 0", this);

        // Customize the label
        QFont font("Arial", 48, QFont::Bold); // Font: Arial, size 48, bold
        label->setFont(font);
        label->setStyleSheet("color: red;"); // Set text color to red
        label->setAlignment(Qt::AlignCenter); // Center align the text

        // Initialize buttons
        button1 = new QPushButton("Increase Counter [um 1]", this);
        button2 = new QPushButton("Increase Counter [um 5]", this);

        // Add widgets to layout
        layout->addWidget(label);
        layout->addWidget(button1);
        layout->addWidget(button2);

        // Connect buttons with lambdas
        connect(button1, &QPushButton::clicked, [this]() { increaseCounter(1); });
        connect(button2, &QPushButton::clicked, [this]() { increaseCounter(5); });

        setLayout(layout);
    }

private slots:
    void increaseCounter(int increment) {
        counter += increment;
        label->setText("Counter: " + QString::number(counter));
    }

private:
    QLabel *label;
    QPushButton *button1;
    QPushButton *button2;
    int counter;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CounterWidget widget;
    widget.setWindowTitle("Counter App");
    widget.show();

    return app.exec();
}

#include "main.moc"
