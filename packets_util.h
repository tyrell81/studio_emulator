/* Copyright Prosoft-Biometrics */

#ifndef HF_CORE_KERNEL_PACKETS_UTIL_H_
#define HF_CORE_KERNEL_PACKETS_UTIL_H_

#include <QByteArray>

template <typename TPacket>
struct PacketIn {
    explicit PacketIn(const QByteArray& ba_packet)
        : ba(ba_packet)
        , packet(reinterpret_cast<const TPacket*>(ba_packet.data()))
    {
    }

    inline const TPacket* operator->() const
    {
        return packet;
    }

    inline bool isValid(const size_t size = 0) const
    {
        if (size)
            return ba.size() == static_cast<int>(size);

        return ba.size() == sizeof(TPacket);
    }

    inline size_t size() const
    {
        return static_cast<size_t>(ba.size());
    }

    template <typename TExtra>
    inline const TExtra* extra(const size_t i) const
    {
        return reinterpret_cast<const TExtra*>(
                   ba.constData() + sizeof(TPacket))
            + i;
    }

protected:
    const QByteArray& ba;

private:
    const TPacket* const packet{ Q_NULLPTR };
};

template <typename TPacket>
using PacketResp = PacketIn<TPacket>;

template <typename TPacket>
struct PacketOut {
    PacketOut()
        : ba({ sizeof(TPacket), 0 })
    {
    }

    explicit PacketOut(const uint8_t cmd)
        : ba({ sizeof(TPacket), 0 })
    {
        (*this)->header.cmd = cmd;
    }

    inline TPacket* operator->()
    {
        return reinterpret_cast<TPacket*>(ba.data());
    }

    inline const QByteArray& operator&() const
    {
        return ba;
    }

    inline void addExtra(const QByteArray& extra)
    {
        ba.append(extra);
    }

protected:
    QByteArray ba;
};

template <typename TPacket>
using PacketRequest = PacketOut<TPacket>;

#endif // HF_CORE_KERNEL_PACKETS_UTIL_H_
