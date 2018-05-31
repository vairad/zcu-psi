#ifndef PACKETCOLUMNORDER_H
#define PACKETCOLUMNORDER_H

enum PacketColumnOrder: int{
    source = 0,
    destination,
    type,
    code,
    identifier,
    sequence,
    data
};

#endif // PACKETCOLUMNORDER_H
