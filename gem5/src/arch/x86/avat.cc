//
// Created by Yan Meng on 16-12-22.
//

#include "arch/x86/avat.hh"
#include <iomanip>

ApproxComputing::Avat *
X86AVATParams::create()
{
    return new ApproxComputing::Avat(this);
}
// Member function in AvatEntry
bool ApproxComputing::AvatEntry::isApproximable(Addr target) {
    //if (target < beginAddr || target > endAddr) return false;
    //return ((target - beginAddr) / (col * elemSize)) % apprLevel == (apprLevel - 1);
    return true;
}

void ApproxComputing::AvatEntry::updateBuffer(ElemType e, Addr addr) {
    buf.push_back(e);
    if(buf.size() > maxBufferSize) buf.pop_front();
    lastAddr = addr;
}

bool ApproxComputing::AvatEntry::isBufferValid() {
    return buf.size() == maxBufferSize;
}

ApproxComputing::AvatEntry::ElemType ApproxComputing::AvatEntry::getValueFromBuffer() {
    ElemType _sum = 0;
    for(auto i : buf) _sum += i;
    return _sum / buf.size();
}

std::string ApproxComputing::AvatEntry::getAddrInfo(Addr addr) {
    std::stringstream ostream;
    int r = (addr - beginAddr) / (elemSize * col);
    int c = (addr - beginAddr - r * col * elemSize) / elemSize;
    ostream << "0x" << std::setbase(16) << addr << std::setbase(10) << ":\trow: " << r
            << "\tcol: " << c;
    return ostream.str();
}

bool ApproxComputing::AvatEntry::isAddrValid(Addr addr) {
    Addr len = addr > lastAddr ? addr - lastAddr : lastAddr - addr;
    return (len / elemSize) <= (maxBufferSize << 1);
}
// Member function in AvatEntry end.

// Member function in Avat
ApproxComputing::Avat::Avat(const Params *p) : SimObject(p) {
    //addEntry(0x601060, 0x601060 + 200 * 200 * 4, 200, 200, 2, 4);
}

void ApproxComputing::Avat::addEntry(Addr begin, Addr end, int _row, int _col, int level, size_t elemSize) {
    this->data.emplace_back(begin, end, _row, _col, level, elemSize);
}

ApproxComputing::AvatEntry* ApproxComputing::Avat::findEntry(Addr target) {
    for (int i = 0; i < this->data.size(); i++) {
        if(this->data[i].getBeginAddr() <= target && target <= this->data[i].getEndAddr())
            return &(this->data[i]);
    }
    return NULL;
}

void ApproxComputing::Avat::removeEntry(Addr beginAddr) {
    for (int i = 0; i < this->data.size(); i++) {
        if(this->data[i].getBeginAddr() == beginAddr)
            this->data.erase(this->data.begin() + i);
    }
}
// Member function in Avat end.

