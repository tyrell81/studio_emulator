/* Copyright Prosoft-Biometrics */

#ifndef HF_CORE_STUDIO_STUDIO_PACKETS_UTIL_H_
#define HF_CORE_STUDIO_STUDIO_PACKETS_UTIL_H_

#include <type_traits>

#include "packets_util.h"

//#include "core/database/settings.h"

#include "pvwtc_studio_packets.h"
//#include "studio_worker.h"

#define SERIAL 0x000000

enum EnrollType {
    kEnrollNone = -1,
    kEnrollCard = 0,
    kEnrollPalm = 1
};

enum PacketResult {
    kResultOk = 0x00,
    kResultFail = 0x01,
    kResultFailInputData = 0x02,
    kResultFailDatabase = 0x03,
    kResultBusy = 0x04,
    kResultNothingToDo = 0x05,
    kResultCmdUnknown = 0xAA,
};

//#ifdef Q_ENUM
//    Q_ENUM(EnrollType);
//    Q_ENUM(PacketResult);
//#else
//    Q_ENUMS(EnrollType);
//    Q_ENUMS(PacketResult);
//#endif

template <typename TPacket>
using StudioPacketIn = PacketIn<TPacket>;

template <typename TPacket, typename TExtra = std::false_type>
struct StudioPacketOut {
    StudioPacketOut(const QByteArray& ba_recv_packet,
        const size_t extra_size = 0)
        : ba_(static_cast<int>(sizeof(TPacket) + sizeof(TExtra) * extra_size), 0)
    {
        auto header = reinterpret_cast<const studio_packet_header_t* const>(
            ba_recv_packet.constData());
        (*this)->header.cmd = header->cmd;
        (*this)->header.addr = SERIAL; //core::Settings::getSerial();
        (*this)->result = PacketResult::kResultOk;
    }

    template <typename T>
    StudioPacketOut(const StudioPacketIn<T>& recv_packet,
        const size_t extra_size)
        : ba_(static_cast<int>(sizeof(TPacket) + sizeof(TExtra) * extra_size), 0)
    {
        (*this)->header.cmd = recv_packet->header.cmd;
        (*this)->header.addr = SERIAL; //core::Settings::getSerial();
        (*this)->result = PacketResult::kResultOk;
    }

    inline TPacket* operator->()
    {
        return reinterpret_cast<TPacket*>(ba_.data());
    }

    inline QByteArray operator&() const
    {
        return ba_;
    }

    inline TExtra* operator[](const size_t i)
    {
        return reinterpret_cast<TExtra*>(ba_.data() + sizeof(TPacket)) + i;
    }

private:
    QByteArray ba_;
};

template <typename TPacket>
struct StudioPacketOut<TPacket> {
    explicit StudioPacketOut(const QByteArray& ba_recv_packet)
    {
        auto header = reinterpret_cast<const studio_packet_header_t* const>(
            ba_recv_packet.constData());
        (*this)->header.cmd = header->cmd;
        (*this)->header.addr = SERIAL; //core::Settings::getSerial();
        (*this)->result = PacketResult::kResultOk;
    }

    explicit StudioPacketOut(const uint8_t cmd)
    {
        (*this)->header.cmd = cmd;
        (*this)->header.addr = 0x00; //core::Settings::getSerial();
    }

    template <typename T>
    explicit StudioPacketOut(const StudioPacketIn<T>& recv_packet)
    {
        (*this)->header.cmd = recv_packet->header.cmd;
        (*this)->header.addr = SERIAL;
        (*this)->result = PacketResult::kResultOk;
    }

    StudioPacketOut(const QByteArray& ba_recv_packet,
        const QByteArray& extra)
        : ba_(static_cast<int>(sizeof(TPacket)) + extra.size(), 0)
    {
        auto header = reinterpret_cast<const studio_packet_header_t* const>(
            ba_recv_packet.constData());

        (*this)->header.cmd = header->cmd;
        (*this)->header.addr = SERIAL;
        (*this)->result = PacketResult::kResultOk;
        memcpy(ba_.data() + sizeof(TPacket), extra.constData(), extra.size());
    }

    StudioPacketOut(const uint8_t& cmd, const QByteArray& extra)
        : ba_(static_cast<int>(sizeof(TPacket)) + extra.size(), 0)
    {
        (*this)->header.cmd = cmd;
        (*this)->header.addr = SERIAL;
        memcpy(ba_.data() + sizeof(TPacket), extra.constData(), extra.size());
    }

    template <typename T>
    StudioPacketOut(const StudioPacketIn<T>& recv_packet,
        const QByteArray& extra)
        : ba_(static_cast<int>(sizeof(TPacket)) + extra.size(), 0)
    {
        (*this)->header.cmd = recv_packet->header.cmd;
        (*this)->header.addr = SERIAL;
        (*this)->result = PacketResult::kResultOk;
        memcpy(ba_.data() + sizeof(TPacket), extra.constData(), extra.size());
    }

    inline TPacket* operator->()
    {
        return reinterpret_cast<TPacket*>(ba_.data());
    }

    inline QByteArray operator&() const
    {
        return ba_;
    }

    template <typename TExtra>
    inline TExtra* addExtra(const size_t extra_count = 1)
    {
        const auto current_size = ba_.size();
        ba_.resize(ba_.size() + sizeof(TExtra) * extra_count);
        return reinterpret_cast<TExtra*>(ba_.data() + current_size);
    }

    inline void addExtra(const QByteArray& extra)
    {
        ba_.append(extra);
    }

    template <typename TExtra>
    inline void addExtraSizeAndExtraData(
        const TExtra value, const QByteArray& extra)
    {
        *addExtra<TExtra>() = value;
        addExtra(extra);
    }

    inline size_t extraSize()
    {
        return ba_.size() - sizeof(TPacket);
    }

protected:
    StudioPacketOut() {}

private:
    QByteArray ba_{ sizeof(TPacket), 0 };
};

template <>
struct StudioPacketOut<studio_packet_out_cmd_c3_t> {
    explicit StudioPacketOut(const QByteArray& ba_recv_packet)
    {
        auto header = reinterpret_cast<const studio_packet_header_t*>(
            ba_recv_packet.constData());
        (*this)->header.cmd = header->cmd;
        (*this)->header.addr = SERIAL;
    }

    inline studio_packet_out_cmd_c3_t* operator->()
    {
        return reinterpret_cast<studio_packet_out_cmd_c3_t*>(ba_.data());
    }

    inline QByteArray operator&() const
    {
        return ba_;
    }

protected:
    StudioPacketOut() {}

private:
    QByteArray ba_{ sizeof(studio_packet_out_cmd_c3_t), 0 };
};

#endif // HF_CORE_STUDIO_STUDIO_PACKETS_UTIL_H_
