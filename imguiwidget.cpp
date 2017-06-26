#include "imguiwidget.h"
#include "imguirenderer.h"
#include <QMouseEvent>
#include <QOpenGLExtraFunctions>

namespace QtImGui {

ImGuiWidget::ImGuiWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_renderer = new ImGuiRenderer(this);
    if (m_instance) {
        qFatal("Cannot create multiple ImGuiWidget instance");
    }
    m_instance = this;
}

void ImGuiWidget::mousePressEvent(QMouseEvent *event)
{
    m_renderer->onMousePressedChange(event);
}

void ImGuiWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_renderer->onMousePressedChange(event);
}

void ImGuiWidget::wheelEvent(QWheelEvent *event)
{
    m_renderer->onWheel(event);
}

void ImGuiWidget::keyPressEvent(QKeyEvent *event)
{
    m_renderer->onKeyPressRelease(event);
}

void ImGuiWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_renderer->onKeyPressRelease(event);
}

void ImGuiWidget::initializeGL()
{
    m_renderer->initialize();

    ImGuiIO &io = ImGui::GetIO();

    io.RenderDrawListsFn = [](ImDrawData *drawData) {
        m_instance->m_renderer->renderDrawList(drawData);
    };
}

void ImGuiWidget::paintGL()
{
    m_renderer->newFrame();
    renderImGui();
    ImGui::Render();
}

ImGuiWidget *ImGuiWidget::m_instance = nullptr;

}
