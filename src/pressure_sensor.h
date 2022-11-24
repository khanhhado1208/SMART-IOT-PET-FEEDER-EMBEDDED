
#include "DigitalIoPin.h"

class pressureSensor{
	private:
		int pressure;
	public:
		pressureSensor();
		virtual ~pressureSensor();
		void start();
		int get_value();
};
