#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <vector>
#include <iostream>

using namespace std;

// Klasse TextPiece
class TextPiece {
public:
    TextPiece(const QPoint& position, const QImage& cellImage)
        : position(position),
          start_position(position),
          cellImage(cellImage) {
            this->targetPosition = QPoint(100,100);
          }

    // Getter für die Position
    QPoint getPosition() const { return position; }

    // Getter für das Bild
    QImage getImage() const { return cellImage; }

    // Prüft, ob die Zelle schwarze Pixel enthält
    static bool containsBlackPixel(const QImage& cell) {
        for (int y = 0; y < cell.height(); ++y) {
            for (int x = 0; x < cell.width(); ++x) {
                QColor pixelColor = cell.pixelColor(x, y);
                if (pixelColor.red() < 100 && pixelColor.green() < 100 && pixelColor.blue() < 100) {
                    return true;
                }
            }
        }
        return false;
    }

    void move(const QPoint& offset)
    {
        this->position += offset;
    }

private:
    QPoint position;
    QPoint start_position;
    QImage cellImage;
    QPoint target_position;
};

// Funktion, um das Bild in TextPiece Objekte zu zerlegen
std::vector<TextPiece> generateTextPieces(const QImage& image, int cellSize) {
    std::vector<TextPiece> pieces;

    for (int y = 0; y < image.height(); y += cellSize) {
        for (int x = 0; x < image.width(); x += cellSize) {
            QRect cellRect(x, y, cellSize, cellSize);
            QImage cell = image.copy(cellRect);

            // Prüfe, ob die Zelle schwarze Pixel enthält
            if (TextPiece::containsBlackPixel(cell)) {
                pieces.emplace_back(QPoint(x, y), cell);
            }
        }
    }
    return pieces;
}

// Hauptklasse zur Darstellung der TextPieces
class ImageWindow : public QWidget {
public:
    ImageWindow(const QString& imagePath, QWidget *parent = nullptr)
        : QWidget(parent), image(imagePath) {

        setWindowTitle("Text Raster Animation");
        pieces = generateTextPieces(image, 10);  // Rastergröße 10x10 Pixel
        cout << "Anzahl der TextPiece Objekte: " <<  pieces.size() << endl; 
        resize(image.size());

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &ImageWindow::updateAnimation);
        timer->start(500);
    }

    

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

         // Hintergrund auf Weiß setzen
        painter.fillRect(this->rect(), Qt::white);

        for (const auto& piece : pieces) {
            painter.drawImage(piece.getPosition(), piece.getImage());
        }
    }

private:
    QImage image;
    std::vector<TextPiece> pieces;

private slots:

    void updateAnimation() {

        for (auto& piece : pieces) {

            piece.move( QPoint(5,0) );

        }
       
        update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Fenster mit Bild erstellen
    ImageWindow window("text_to_animate.png"); // Bildpfad anpassen
    window.show();

    return app.exec();
}
