//
// Created by Yan Meng on 16-12-22.
//

#ifndef SRC_AVAT_H
#define SRC_AVAT_H

// Approximable Virtual Address Table. Every time CPU reads a virtual address we have to
// check whether the memory address can be approximated in cache.

#include "params/X86AVAT.hh"
#include "sim/sim_object.hh"
#include <vector>
#include <deque>

namespace ApproxComputing {

struct ApproxArgs{
    Addr beginAddr;
    int row;
    int col;
    int apprLevel;
    size_t elemSize;
};

// This class is an entry in the table;
class AvatEntry{
    public:
        typedef int ElemType;
    private:
        Addr beginAddr;
        Addr endAddr;
        int row;
        int col;
        int apprLevel;
        size_t elemSize;
        std::deque<ApproxComputing::AvatEntry::ElemType> buf;
        size_t maxBufferSize;
        Addr lastAddr;

    public:
        AvatEntry(Addr begin, Addr end, int _row, int _col, int level, size_t _elemSize) :
                beginAddr(begin), endAddr(end), row(_row), col(_col), apprLevel(level), elemSize(_elemSize),
                maxBufferSize(8)
        {};

        // Functions to get members.
        Addr getBeginAddr() {return beginAddr;}
        Addr getEndAddr() {return endAddr;}
        int getRow() {return row;}
        int getCol() {return col;}
        int getApproximateLevel() {return apprLevel;}
        size_t getElemSize() {return elemSize;}

        // Return whether an address is approximable.
        bool isApproximable(Addr target);
        void updateBuffer(ElemType e, Addr addr);
        bool isBufferValid();
        ElemType getValueFromBuffer();
        size_t getBufferSize() {return buf.size();}
        void clearBuffer() {buf.clear();}
        bool isAddrValid(Addr addr);

        // Helper functions
        std::string getAddrInfo(Addr addr);
    };


class Avat : public SimObject{
    public:
        typedef X86AVATParams Params;
        Avat(const Params *p);

        // Add an entry to table.
        void addEntry(Addr begin, Addr end, int _row, int _col, int level, size_t elemSize);

        // Find whether address target is contained in the table. If we find the corresponding entry, we will
        // return a pointer pointed to it. Otherwise return NULL;
        ApproxComputing::AvatEntry *findEntry(Addr target);

        // Remove an entry from the table.
        void removeEntry(Addr beginAddr);
    private:
        // All entries stored in this vector.
        std::vector<ApproxComputing::AvatEntry> data;
    };

};


#endif //SRC_AVAT_H
