#ifndef PACKETCOLUMNORDER_H
#define PACKETCOLUMNORDER_H

enum PacketColumnOrder: int{
    timestamp = 0,
    source,
    destination,
    type,
    code,
    identifier,
    sequence,
    data
};

#endif // PACKETCOLUMNORDER_H
