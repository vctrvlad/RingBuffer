/*

 * RingBuffer.h
 *
 * Created: 5/26/2018 2:52:02 PM
 *  Author: Victor
 */ 

/*usage requirements:
provide the buffer to operate on.eg: 
uint8_t pRxMemory[255];
instantiate the object eg.:
RingBuffer rxRb(255, pRxMemory);*/

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

class RingBuffer
{
	private:
	uint16_t size;
	uint8_t *pBuffer;
	uint16_t head;
	uint16_t tail;
	uint16_t cnt;
	uint8_t msgCnt;
	
	public:
	/*constructor of the ring buffer, only the size is variable among the instantiated objects, the rest are initialized to ZERO*/
	RingBuffer(const uint16_t argSize, uint8_t *argPBuffer): size(argSize), pBuffer(argPBuffer) {this->head = 0; this->tail = 0; this->cnt = 0;};
		
	/*method that takes a byte and stores it in the buffer if there is enough room left*/
	uint8_t push(uint8_t argRxChar);
	
	/*method that pops an element from the ring buffer if there is one, 
	and stores it into a pointer variable to a byte*/
	uint8_t popElement(uint8_t *pArgPElement);

	/*method to be used in order to check the buffer is full.
	It'll return 1 in case the buffer is full, and 0 in oposite.*/
	uint8_t isFull(){ return cnt > (size-1) ? 1 : 0;};
		
	/*method to be used to check the buffer has something inside.
	will return 0 if nothing to read, and 1 in opposite*/
	uint8_t isElement(){ return cnt ? 1 : 0;};
		
	/*method that uses the popElement method in order to extract
	an entire message from the buffer. The message will be stored
	in the provided buffer as a pointer to an array.
	Returns 0 in case of null pointer passed*/
	uint8_t popMessage(uint8_t *pArgPMessage);
};



#endif /* RINGBUFFER_H_ */