/* Copyright Prosoft-Biometrics */

#ifndef HF_KERNEL_QT_5_4_QCINFO_H_
#define HF_KERNEL_QT_5_4_QCINFO_H_

#include <QLoggingCategory>

#ifdef qCInfo
#define HFLoggingCategory QLoggingCategory
#define Q_CATEGORY(name) name
#endif

#ifndef qCInfo

#define QtInfoMsg static_cast<QtMsgType>(QtSystemMsg + 1)
#define Q_CATEGORY(name) name, "$info$" name

#define Q_LOGGING_CATEGORY_ENABLE(name, type, value) \
    const_cast<Q_5_4_LoggingCategory&>(name()).setEnabled(type, value);

#define qInfo QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug

class Q_5_4_LoggingCategory : public QLoggingCategory {
    Q_DISABLE_COPY(Q_5_4_LoggingCategory)

public:
    explicit Q_5_4_LoggingCategory(const char* category, const char* info_category)
        : QLoggingCategory(category)
        , info_name(info_category)
    {
        setEnabled(QtInfoMsg, true);
    }

    Q_5_4_LoggingCategory(const char* category, QtMsgType severityLevel)
        : QLoggingCategory(category, severityLevel)
    {
        setEnabled(QtInfoMsg, true);
    }

    ~Q_5_4_LoggingCategory()
    {
    }

    // allows usage of both factory method and variable in qCX macros
    Q_5_4_LoggingCategory& operator()() { return *this; }
    const Q_5_4_LoggingCategory& operator()() const { return *this; }

    const char* infoName() const { return info_name; }

    //bool isEnabled(QtMsgType type) const;
    void setEnabled(QtMsgType type, bool enable)
    {
        switch (type) {
#ifdef Q_ATOMIC_INT8_IS_SUPPORTED
        case QtInfoMsg:
            bools.enabledInfo.store(enable);
            break;
#else
        case QtInfoMsg:
            setBoolLane(&enabled, enable, InfoShift);
            break;
#endif
        default:
            QLoggingCategory::setEnabled(type, enable);
            break;
        }
    }

#ifdef Q_ATOMIC_INT8_IS_SUPPORTED
    bool isInfoEnabled() const
    {
        return bools.enabledInfo.load();
    }
#else
    bool isInfoEnabled() const
    {
        return enabled.load() >> InfoShift & 1;
    }
#endif

private:
    const char* info_name;

#ifdef Q_BIG_ENDIAN
    enum { InfoShift = 24 };
#else
    enum { InfoShift = 0 };
#endif

    struct AtomicBools {
#ifdef Q_ATOMIC_INT8_IS_SUPPORTED
        QBasicAtomicInteger<bool> enabledInfo;
#endif
    };
    union {
        AtomicBools bools;
        QBasicAtomicInt enabled;
    };
};
#define HFLoggingCategory Q_5_4_LoggingCategory

#undef Q_DECLARE_LOGGING_CATEGORY
#undef Q_LOGGING_CATEGORY

#define Q_DECLARE_LOGGING_CATEGORY(name) \
    extern const HFLoggingCategory& name();

#if defined(Q_COMPILER_VARIADIC_MACROS) || defined(Q_MOC_RUN)

#define Q_LOGGING_CATEGORY(name, ...)                                               \
    const HFLoggingCategory& name()                                                 \
    {                                                                               \
        static const HFLoggingCategory category(__VA_ARGS__, "$info$" __VA_ARGS__); \
        return category;                                                            \
    }

#define qCInfo(category, ...)                                                                                     \
    for (bool qt_category_enabled = category().isInfoEnabled(); qt_category_enabled; qt_category_enabled = false) \
    QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, category().infoName()).debug(__VA_ARGS__)

#else // defined(Q_COMPILER_VARIADIC_MACROS) || defined(Q_MOC_RUN)

// Optional msgType argument not supported
#define Q_LOGGING_CATEGORY(name, string)                 \
    const HFLoggingCategory& name()                      \
    {                                                    \
        static const HFLoggingCategory category(string); \
        return category;                                 \
    }

// check for enabled category inside Q_5_4_LoggingCategory.
#define qCInfo qInfo

#endif // Q_COMPILER_VARIADIC_MACROS || defined(Q_MOC_RUN)

#else

#define Q_LOGGING_CATEGORY_ENABLE(name, type, value) \
    const_cast<QLoggingCategory&>(name()).setEnabled(type, value);

#endif // qCInfo

#endif // HF_KERNEL_QT_5_4_QCINFO_H_
