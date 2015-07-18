// RangeInfoList.cpp
//

#include "RangeInfoList.h"
#include "IDrawable.h"
#ifdef __AVR_ATmega328P__
#include "new.h"
#endif

RangeInfoList::RangeInfoList (int rangeId, uint16_t offset, uint16_t size, bool reversed)
{
	this->rangeId = rangeId;
	this->offset = offset;
	this->size = size;
	this->startTime = 0;
	this->refreshCount = 0;
	this->reversed = reversed;
	next = NULL;
	listItem = NULL;
}
RangeInfoList::~ RangeInfoList ()
{
	clear();
}

void RangeInfoList::clear ()
{
	RangeInfoList *cur = next;
	// delete our lists, we do not actually delete the first item, as it was not 
	// dynamically allocated
	while(cur != NULL) {
		RangeInfoList *deleteme = cur;
		cur = cur->next;
		delete deleteme;
	}
	this->startTime = 0;
	this->refreshCount = 0;
	this->reversed = false;
	next = NULL;
	listItem = NULL;
}

RangeInfoList* RangeInfoList::add (int rangeId, uint16_t offset, uint16_t size, bool reversed)
{
	if(next == NULL) {
		this->next = new RangeInfoList(rangeId, offset, size, reversed);
		return this->next;
	}
	else {
		return this->next->add(rangeId, offset, size, reversed);
	}
}

void RangeInfoList::clearAll ()
{
	this->startTime = 0;
	this->refreshCount = 0;
	this->refreshCount = 0;
	this->reversed = false;
	listItem = NULL;
	if(this->next != NULL)
		return this->next->clearAll();

}

void RangeInfoList::clearEffect (int rangeId)
{
	if(this->rangeId == rangeId) {
		this->startTime = 0;
		this->refreshCount = 0;
		this->refreshCount = 0;
		listItem = NULL;
	}
	else if(this->next != NULL)
		return this->next->clearEffect(rangeId);
}

// removes a range from the list
bool RangeInfoList::remove(int rangeId) {
	if(this->rangeId == rangeId) {
		// we are not a doubly linked list. cannot handle this case
		return false;
	}
	else if(this->next != NULL) {
		if(this->next->rangeId == rangeId) {
			RangeInfoList * tmp = this->next->next;
			delete this->next;
			this->next = tmp;
			return true;
		}
		else
			return this->next->remove(rangeId);
	}
	else {
		return false;
	}
}

IDrawable * RangeInfoList::getEffect(int rangeId) {
	if(this->rangeId == rangeId) {
		return this->listItem;
	}
	else if (this->next != NULL) {
		return this->next->getEffect(rangeId);
	}
	else
		return NULL;
}

// sets the effect for a particular ragne
void RangeInfoList::setEffect(int rangeId, IDrawable & sequence) {
	if(this->rangeId == rangeId) {
		this->listItem = &sequence;
		this->startTime = millis();
		this->refreshCount = 0;
		this->hasArgs = false;
		sequence.serialize(this->contextArgs, ARG_SIZE);
	}
	else if(this->next != NULL)
		this->next->setEffect(rangeId, sequence);
}


bool RangeInfoList::containsRange(int rangeId) {
	if(this->rangeId == rangeId)
		return true;
	else if(this->next == NULL)
		return false;
	else
		return this->next->containsRange(rangeId);
}

