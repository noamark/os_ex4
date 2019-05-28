#include "VirtualMemory.h"
#include "PhysicalMemory.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~ Helper function ~~~~~~~~~~~~~~~~~~~~~~~~~~

void translate_address(word_t pageNumber, word_t offset, uint64_t* address){
    *address = static_cast<uint64_t > (pageNumber * PAGE_SIZE + offset);
}

/***
 *
 * @param pageNumber
 * @param offset
 * @param nextPageNumber
 * @return 0 if Page was found in the memory, -1 if the page wasn't in the PhysicalMemory (0 was found).
 */
int findPage(word_t pageNumber, word_t offset, word_t* nextPageNumber){
    uint64_t PageAddress = 0;
    translate_address(pageNumber,offset, &PageAddress);
    PMread(PageAddress, nextPageNumber);
    if(*nextPageNumber == 0){
        return -1;
    }
    return 0;
}

void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

int getNextAddress(uint64_t virtualAddress, word_t* offset, uint64_t depth);

int findNewFrame(word_t* frameNumber);

int findFrame(uint64_t virtualAddress, uint64_t* physicalAddress){
    word_t current_offset = 0;
    word_t page_number = 0;
    word_t next_page_number = 0;
    uint64_t depth = 0;
    uint64_t pyshical_address = 0;

//    for(uint64_t depth = 0; depth < page_depth; depth++){
//        getNextAddress(virtualAddress, &current_offset,depth);
//
//    }
//
    while(getNextAddress(virtualAddress, &current_offset,depth)){
            if(findPage(page_number, current_offset, &next_page_number) < 0){
                // find an unused frame or evict a page, suppose this frame number is f1
                findNewFrame(&next_page_number);
                // initialize all f1 contents to 0. (clearTable)
                clearTable(static_cast<uint64_t >(next_page_number));
                // set the pointer of the table to point to f1.
                translate_address(page_number, current_offset, &pyshical_address);
                PMwrite(pyshical_address, next_page_number);
            }

            depth = depth + 1;
    }
    // now the offset is offset of the physical frame, and the page_number is the frame number.
    if(findPage(page_number, current_offset, &page_number) < 0){
        // find an unused frame or evit a page, suppose this frame number is f2

        // restore the page we are looking for to frame f2

        // set the pointer of the table to point to f2.


    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~ Libary function ~~~~~~~~~~~~~~~~~~~~~~~~~~


void VMinitialize() {
    clearTable(0);
}

int VMread(uint64_t virtualAddress, word_t* value) {
    uint64_t physicalAddress = 0;
    findFrame(virtualAddress, &physicalAddress);
    VMread(physicalAddress, value);
    return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value) {
    uint64_t physicalAddress = 0;
    findFrame(virtualAddress, &physicalAddress);
    VMwrite(physicalAddress, value);
    return 1;
}
