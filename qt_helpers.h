/* Copyright Prosoft-Biometrics */

#ifndef HF_CORE_KERNEL_QT_HELPERS_H_
#define HF_CORE_KERNEL_QT_HELPERS_H_

#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QThread>

#include "qt_5.4_qcinfo.h"

template <class... Args, class T, class R>
auto qOverload(R (T::*m)(Args...)) -> decltype(m)
{
    return m;
}

template <class T, class R>
auto qOverload(R (T::*m)()) -> decltype(m)
{
    return m;
}

#endif // HF_CORE_KERNEL_QT_HELPERS_H_
