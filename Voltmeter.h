#pragma once 

#define DEF_VOLT_PORT	(A4)

//전압
class Voltmeter 
{
public: 
	Voltmeter(void) 
	{
		setPort(DEF_VOLT_PORT); 
	}
	~Voltmeter() 
	{

	}

	
	int getVoltStep(void) const
	{
		int nVolt = analogRead(m_nPort);
		return nVolt;
	}

	double getVolt(void) const
	{
		int nVolt = getVoltStep();
		double volt = nVolt / 1023. * 5.;
		return volt;
	}

	void setPort(int nPort)
	{
		m_nPort = nPort;
	}

private: 
protected: 
	int m_nPort;
};