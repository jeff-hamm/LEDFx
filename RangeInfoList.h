// RangeInfoList.h
//

#ifndef RangeInfoList_h
#define RangeInfoList_h
#include <arduino.h>
#include <stdarg.h>

#define ARG_SIZE 10
class IDrawable;


// a list of LED effect lists. Primarily for internal use
class RangeInfoList
{
private:
public:
  RangeInfoList * next;
  IDrawable * listItem;
  int rangeId;
  bool reversed;
  uint16_t offset;
  uint16_t size;
  uint32_t startTime;
  uint32_t lastRefreshTime;
  uint16_t refreshCount;
  char contextArgs[ARG_SIZE];
  bool hasArgs;

  RangeInfoList (int rangeId, uint16_t offset, uint16_t size, bool reversed = false);
  ~ RangeInfoList ();
  // clears the list and frees any dynamically allocated items.
  void clear ();
 
  // clears any range effects
  void clearAll ();
  // clears the effect on the specified range
  void clearEffect (int rangeId);
  // adds a new item to this list
  RangeInfoList* add (int rangeId, uint16_t offset, uint16_t size, bool reversed = false);
  // removes a range from the list. returns true if it was removed
  bool remove(int rangeId);
  // sets the effect for a particular range
  void setEffect(int rangeId, IDrawable & sequence);
  // sets the effect for a particular range and specifies the any context arguments that
  void setEffectWithArgs(int rangeId, IDrawable & effect);
  // determines if a sequence with the specified range already exists
  bool containsRange(int rangeId);
  // gets the current effect at the specified range
  IDrawable * getEffect(int rangeId);
};
#endif