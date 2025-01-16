#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QPointF>
#include <vector>
#include <iostream>

#include <stdlib.h> // für rand()

using namespace std;

// Klasse TextPiece
class TextPiece {
public:
    TextPiece(const QPoint& position, const QImage& cellImage, uint height, uint width)
        : position(position),
          start_position(position),
          cellImage(cellImage) {

            uint rndx = rand() % width;
            uint rndy = rand() % height;
            this->target_position = QPoint( rndx, rndy );

            this->delta_position = ((QPointF) (target_position - start_position)) * 0.10;
          }

    // Getter für die Position
    QPointF getPosition() const { return position; }

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

    void simulation_step()
    {
        this->position += this->delta_position;
        if (this->position.toPoint() == this->target_position)
        {
            this->delta_position = -this->delta_position;
        }
        if (this->position.toPoint() == this->start_position)
        {
            this->delta_position = QPointF(0.0,0.0);
        }
    }

private:
    QPointF position;
    QPointF delta_position;

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
                pieces.emplace_back(QPoint(x, y), cell, image.height(), image.width());
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

            //piece.move( QPoint(5,5) );
            piece.simulation_step();

        }
       
        update();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPoint startpos(5, 19);
    QPoint targetpos(100,100);
    QPointF diff = ((QPointF) (targetpos - startpos)) * 0.1;
    std::cout << "QPointF: (" << diff.x() << ", " << diff.y() << ")\n";

    // Fenster mit Bild erstellen
    ImageWindow window("text_to_animate.png"); // Bildpfad anpassen
    window.show();

    return app.exec();
}
