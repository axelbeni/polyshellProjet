
#include "CArc.hpp"

CArc::CArc() {

}
void CArc::ARCAfficher() {
	std::cout << uiARCDestination << std::endl;

}

 unsigned int CArc::ARCLireDestination()
{
	return uiARCDestination;
}
 void  CArc::ARCEcrireDestination(unsigned int uiValue) {
	uiARCDestination =uiValue;
}

CArc::CArc(unsigned int uiValue)
{
	ARCEcrireDestination( uiValue);
}

CArc::CArc(CArc & ARCParam)
{
	uiARCDestination = ARCParam.uiARCDestination;
}

