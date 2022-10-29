/*
 * Jovihanni Caseñas
 * BSCpE 4A
 * CPE 411 Embedded Systems 
 * Activity 5 - Memory, Memory Testing, and Peripheral
 *
 * This C++ code is the implementation of cyclic redundancy check [crc]
 * 
 * The user shall input a binary sent and received data
 * as well as the key which will serve as the divisor
 * The sent data will be appended to the right
 * with n number of zeroes
 * wherein n is equal to the length of key - 1
 * The new sent data shall be divided by the key
 * The remainder shall be appended to the original
 * sent data
 * The received data shall then be divided by
 * the same key and the remainder shall be evaluated
 * If the remainder is zero, then no error is detected
 * otherwise, an error message is printed
 */

#include <iostream>
#include <string>
using namespace std;

string getCRC(string sent, string key);
string appendZeroes(string sent, int keyLen);
string compareMSB(string dividend);
string exor(string dividend, string key);
string division(string dividend, string key);
bool validation(string rem);

/* This is the main function of the program */
int main(int argc, char** argv) {
	string sent, received, key;
	string appendedCRC, receiverRem;
	
	cout<<"Sent binary data: ";
	cin>>sent;
	
	cout<<"Received binary data: ";
	cin>>received;
	
	cout<<"Binary key: ";
	cin>>key;
	
	/*
	 * calculating the crc and appending it to
	 * the sent binary data
	 */
	appendedCRC = getCRC(sent, key);
	
	/*
	 * calculating the remainder
	 * from dividing the received data
	 * by the key
	 */
	receiverRem = division(received, key);
	
	
	/*
	 * function to validate if there is an 
	 * error in the transmission of data
	 */
	bool noError = validation(receiverRem);
	
	/* output messages */
	if (noError) {
		cout<<"No error detected.";
	} else {
		cout<<"Error detected.";
	}
	
	return 0;
}

/*
 * function to append zeroes to the sent data
 * as well as to calculate the remainder or the crc
 */
string getCRC(string sent, string key) {
	int keyLen = key.length();
	string sentAppended, rem;
	
	sentAppended = appendZeroes(sent, keyLen);
	
	rem = division(sentAppended, key);
	
	return sent + rem;
}

/* appending zeroes to the sent data */
string appendZeroes(string sent, int keyLen) {
	string result = sent;
	
	for (int i = 1; i < keyLen; i++) {
		result.append("0");
	}
	
	return result;
}

/*
 * function that performs division
 * this is used in dividing the sent
 * and received data
 */
string division(string dividend, string key) {
	int keyLen = key.length();
	string subDividend, divisor;
	string quotient = "";
	string rem, result, bit;
	
	for (int i = 0; i < dividend.length(); /*VOID*/) {
		if (i == 0) {
			subDividend = dividend.substr(0, keyLen);
			i = keyLen;
		} else {
			subDividend = rem.substr(1, keyLen - 1) + dividend[i];
			i++;
		}
		
		bit = compareMSB(subDividend);
		quotient += bit;
		if (bit == "0") {
			divisor = "";
			for (int i = 0; i < keyLen; i++) {
				divisor += "0";
			}
		} else {
			divisor = key;
		}
		rem = exor(subDividend, divisor);
	}
	
	result = rem.substr(1, keyLen - 1);
	
	return result;
}

/*
 * part of the division process
 * the purpose of this block of code
 * is to compare the most significant
 * bit of the subdividend and the divisor
 * if the leftmost bit of the subdividend
 * is one then the quotient shall be appended
 * with one, otherwise, append zero
 */
string compareMSB(string dividend) {
	if (dividend[0] == '1') {
		return "1";
	}
	return "0";
}

/*
 * this is part of the long division process
 * the purpose of this block of code
 * is to subtract the subdividend and
 * the product from multiplying one
 * bit of the quotient to the divisor
 */
string exor(string dividend, string key) {
	string result = "";
	
	for (int i = 0; i < key.length(); i++) {
		if (dividend[i] != key[i]) {
			result += "1";
		} else {
			result += "0";
		}
	}
		
	return result;
}


/*
 * function to check if there is
 * no error in the data transmission
 */
bool validation(string rem) {
	for (int i = 0; i < rem.length(); i++) {
		if (rem[i] == '1') {
			return false;
		}
		return true;
	}
}
