//
// Copyright (c) 2010-2015 Marat Abrarov (abrarov@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MA_ECHO_SERVER_QT_MAINFORM_H
#define MA_ECHO_SERVER_QT_MAINFORM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <vector>
#include <boost/system/error_code.hpp>
#include <QWidget>
#include <ma/echo/server/session_config.hpp>
#include <ma/echo/server/session_manager_config.hpp>
#include <ma/echo/server/session_manager_stats_fwd.hpp>
#include <ma/detail/tuple.hpp>
#include <ui_mainform.h>
#include "service_fwd.h"
#include "servicestate.h"
#include "execution_config.h"

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

namespace ma {
namespace echo {
namespace server {
namespace qt {

class MainForm : public QWidget
{
  Q_OBJECT //-V524

public:
  MainForm(Service& service, QWidget* parent = 0, Qt::WindowFlags flags = 0);
  ~MainForm();

private slots:
  void on_startButton_clicked();
  void on_stopButton_clicked();
  void on_terminateButton_clicked();
  void on_statsTimer_timeout();

  void on_service_exceptionHappened();
  void on_service_startCompleted(const boost::system::error_code&);
  void on_service_stopCompleted(const boost::system::error_code&);
  void on_service_workCompleted(const boost::system::error_code&);

private:
  typedef detail::tuple<execution_config, session_manager_config> ServiceConfig;
  typedef detail::tuple<int, QWidget*> OptionWidget;

  Q_DISABLE_COPY(MainForm)

  execution_config       buildExecutionConfig() const;
  session_config         buildSessionConfig() const;
  session_manager_config buildSessionManagerConfig() const;
  ServiceConfig          buildServiceConfig() const;

  void startStatsTimer();
  void stopStatsTimer();
  void conditionalStopStatsTimer(ServiceState::State state);
  void showConfigError(const QString& message, QWidget* widget = 0);
  void showStats(const session_manager_stats& stats);
  void writeLog(const QString& message);
  void updateWidgetsStates(bool ignorePrevServiceState = false);
  static QString buildServiceStateWindowTitle(ServiceState::State state);

  Ui::mainForm ui_;
  QTimer*      statsTimer_;
  std::vector<OptionWidget> optionsWidgets_;
  ServiceState::State       prevServiceState_;
  Service&                  service_;
}; // class MainForm

} // namespace qt
} // namespace server
} // namespace echo
} // namespace ma

#endif // MA_ECHO_SERVER_QT_MAINFORM_H
