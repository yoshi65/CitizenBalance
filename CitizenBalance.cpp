#include "CitizenBalance.h"
 
//#define CIT_DEBUG 

CitizenBalance::CitizenBalance(std::string tty):port(io), port_dev(port){
	port.open(tty);
	port.set_option(asio::serial_port_base::baud_rate(9600));
	port.set_option(boost::asio::serial_port_base::character_size(8));
	port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
	port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none)); 
	//is.push(boost::iostreams::regex_filter{boost::regex{"\e(.*?)\\."}, ""});
	is.push(port_dev);
}


string CitizenBalance::readline(){
	string ret;
	cout << "Getting String." << endl;
	char c;

	do{
		is.read(&c, 1);
		ret += c;
		cout << c;
	}while(c != '\n');	

	/*
	char buff[26];

	port_dev.read(buff, 26);

	cout.write(buff,26);
	cout.flush();

	*/
	//cout << ret << endl;

	return ret;	
}

double CitizenBalance::get_mass(){
	write(port, boost::asio::buffer("[W]", 3));
	//port.flush();          	
		                   
	/*
	int n = read (fd, in_buff, 26);
	int sign = (in_buff[4] == '-'? -1 : 1);
	double val = strtod(&in_buff[5], NULL);
	val *= sign;
	*/
	return 0;
}

int CitizenBalance::testcommand(){
	/*cout << write (fd, "[]", 2) << endl;          	
	usleep ((26 + 5) * 10000);
		                   
	std::string s = readline();
	*/
}

std::string CitizenBalance::get_mass_string(){
	cout << write(port,boost::asio::buffer("[W]", 3)) << endl;          	
		                   
	std::string s = readline();
	//int n = read (fd, in_buff, 26);
	
	return s; //std::string(in_buff, 24);
}


void CitizenBalance::tare(){
	cout << "Taring" << endl;
	write(port, boost::asio::buffer("[W]", 3));
	cout << readline() << endl;
}


CitizenBalance::~CitizenBalance(){
	//is.close();
	port.close();
}

#ifdef CIT_DEBUG

int main(int argc, char *argv[]){
	CitizenBalance cb("/dev/ttyS0");
	//cout << cb.get_mass_string() << endl;
	cout << "w to get weight" << endl << "t to tare" << endl << "q to quit" << endl;

	char in;
	do{
		std::cin >> in;
		if(in == 'w'){
			cout << cb.get_mass() << endl;
		}else if(in == 't'){
			cb.tare();
		}
	}while(in != 'q');
	

	return 0;
}


#endif


