#include "threelayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreeLayer w;
    w.show();
    return a.exec();
}
