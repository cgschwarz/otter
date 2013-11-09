#include "TabBarWidget.h"

#include <QtGui/QContextMenuEvent>
#include <QtWidgets/QMenu>

namespace Otter
{

TabBarWidget::TabBarWidget(QWidget *parent) : QTabBar(parent),
	m_clickedTab(-1)
{
}

void TabBarWidget::contextMenuEvent(QContextMenuEvent *event)
{
	m_clickedTab = tabAt(event->pos());

	QMenu menu(this);
	menu.addAction(QIcon(":/icons/tab-new.png"), tr("New Tab"), this, SIGNAL(requestOpen()));

	if (m_clickedTab >= 0)
	{
		menu.addAction(QIcon(":/icons/tab-close.png"), tr("Close Tab"), this, SLOT(closeCurrent()));

		if (count() > 1)
		{
			menu.addAction(QIcon(":/icons/tab-close-other.png"), tr("Close Other Tabs"), this, SLOT(closeOther()));
		}
	}

	menu.exec(event->globalPos());

	m_clickedTab = -1;
}

void TabBarWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (tabAt(event->pos()) < 0)
	{
		emit requestOpen();
	}
}

void TabBarWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MidButton)
	{
		const int tab = tabAt(event->pos());

		if (tab >= 0)
		{
			emit requestClose(tab);
		}
	}
}

void TabBarWidget::closeCurrent()
{
	if (m_clickedTab >= 0)
	{
		emit requestClose(m_clickedTab);
	}
}

void TabBarWidget::closeOther()
{
	if (m_clickedTab >= 0)
	{
		emit requestCloseOther(m_clickedTab);
	}
}

}