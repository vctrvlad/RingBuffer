/*
 * RingBuffer.cpp
 *
 * Created: 6/6/2018 8:26:41 PM
 *  Author: Victor
 */ 
#include <avr/io.h>
#include "RingBuffer.h"

/*method that takes a byte and stores it in the buffer if there is enough room left*/
uint8_t RingBuffer::push(uint8_t argRxChar)
{
	uint8_t retVal = 0;
	/*make sure there is enough room in order not to overwrite any element*/
	if (isFull())
	{
		/*discard the data, buffer is already full*/
		retVal = 0;
	}
	else
	{
		/*push the new element in the buffer*/
		pBuffer[head] = argRxChar;
		/*count in the new pushed element*/
		cnt++;
		/*evaluate the position of the last element and rotate the pointer if max reached*/
		size > head ? head++ : (head = 0);
		retVal = 1;
	}
	return retVal;
}

/*method that pops an element from the ring buffer if there is one, 
and stores it into a pointer variable to a byte*/
uint8_t RingBuffer::popElement(uint8_t *pArgPElement)
{
	uint8_t retVal = 0;
	
	if(!isElement())
	{
		/*there is no element in the buffer*/
		retVal = 0;
	}
	else
	{
		/*pop the oldest element available*/
		*pArgPElement = pBuffer[tail];
		/*count out the new pushed element*/
		cnt--;
		(size-1) > tail ? tail++ : tail = 0;
		retVal = 1;
	}
	
	return retVal;
}


/*method that uses the popElement method in order to extract
an entire message from the buffer. The message will be stored
in the provided buffer as a pointer to an array.
Returns 0 in case of null pointer passed*/
uint8_t RingBuffer::popMessage(uint8_t *pArgPMessage)
{
	uint8_t retval = 0;
	if (pArgPMessage)
	{
		uint8_t lengthIndex = 0;
		do
		{
			/*loop until there is no element anymore, or null 0x0d character encountered*/
			popElement(&pArgPMessage[lengthIndex]);
		}while (isElement() && (0x0d != pArgPMessage[lengthIndex++]));
		retval = 1;
	}
	else
	{
		retval = 0;
	}
		
	return retval;
}