#ifndef SNECE_CONTROLLER_H
#define SNECE_CONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QVector>

class QPoint;

namespace scene {

class SceneController : public QObject
{
	Q_OBJECT
public:
	explicit SceneController(QObject *parent = 0);

signals:
	void newLineAdded(const QVector<QPoint> &points, const QPoint &newPoint);

public slots:
	void addPoint(int x, int y);
	void clear();

	void drawEnds(int xNew, int yNew);

private:
	QVector<QPoint> mPoints;
	QPoint mNewPoint;
};

}  // namespace scene

#endif  // SNECE_CONTROLLER_H
