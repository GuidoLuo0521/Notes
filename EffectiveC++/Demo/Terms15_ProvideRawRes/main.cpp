#include <QCoreApplication>
#include <QDebug>

#define PRINT_FUNCTION_NAME qDebug() << __FUNCTION__

class FontHandle
{
public:

};


class Font
{
public:
    explicit Font(FontHandle* ph) : m_fh(ph)
    {
        PRINT_FUNCTION_NAME;
    };
    ~Font()
    {
        PRINT_FUNCTION_NAME;
        releaseFont(m_fh);
    }

    static void releaseFont(FontHandle* f)
    {
        Q_UNUSED(f);
        PRINT_FUNCTION_NAME;
    }

    // 显示
    FontHandle* get() const
    {
        PRINT_FUNCTION_NAME;
        return m_fh;
    }

    // 隐示
    // operator 类型(){……}就将类自定义转换成某一特定类型
    operator FontHandle*() const
    {
        PRINT_FUNCTION_NAME;
        return m_fh;
    }

private:
    FontHandle* m_fh;
};


void changeFontSize(FontHandle*, const int )
{
    PRINT_FUNCTION_NAME;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Font font(new FontHandle);

    // 这里就是隐式转换
    changeFontSize(font, 20);

    return a.exec();
}
