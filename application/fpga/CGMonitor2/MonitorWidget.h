#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H



#include <QTabWidget>
#include <QItemSelection>
#include <QTimer>
#include "SummaryTab.h"
#include "FinishedTaskTab.h"
#include "HistorySummaryTab.h"
#include "IOModuleTab.h"
#include "OngoingTaskTab.h"
#include "SupportedOptTab.h"




QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE





//! [0]
class MonitorWidget : public QTabWidget
{
    Q_OBJECT

public:
    MonitorWidget(QWidget *parent=0);

public slots:
    void onTimerOut();
    void hideNow();
    void ShowSum();
    void ShowHistory();
    void ShowOngoing();
    void showSupport();
    void showFinished();

    void Add10LittleFuzai();
    void Add1LargeFuzai();

signals:

public:
      SummaryTab *summaryTab;
      FinshedTaskTab *finshedTab;
      HistorySummaryTab *HistoryTab;
      IOModuleTab *IOTab;
      OngoingTaskTab *OnGoingTab;
      SupportedOptTab* supportTab;

      QTimer* m_timer;

};
//! [0]





#endif // MONITORWIDGET_H
