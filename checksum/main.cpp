/*
 * Jovihanni Caseñas
 * BSCpE 4A
 * CPE 411 Embedded Systems 
 * Activity 5 - Memory, Memory Testing, and Peripheral
 *
 * This C++ code is the implementation of checksum
 *
 * The user inputs the sent and received binary data
 * as well as the block size of the data
 * The program prints an error message if the data
 * input are of not the same length
 * The sent and received data is broken into blocks with 
 * remainder leftmost bits being inserted with zeroes
 * to the left
 * Sent data blocks are added and the sum is
 * converted to one's complement
 * This complement is then added to the sum of the
 * received data blocks
 * If the sum is all 1s, no error is detected
 * otherwise, an error message is printed
 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string getBlocks(string data, string blocks[], int blockSize);
string addBlocks(string add1, string add2);
string onesComplement(string sum);
bool validate(string recSum, string complement);
bool sameLength(string sent, string received);


/*
 * main function of the program
 * asks for sent and received data from the user
 * asks for the block size
 * the data inputs will be compared for the checksum
 */
int main(int argc, char** argv) {
	string sent, received, sentBlocks[50], receivedBlocks[50];
	string checkSum, complement, receivedValidate;
	int blockSize;
	bool validation;
	
	cout<<"Sent binary data: ";
	cin>>sent;
	
	cout<<"Received binary data: ";
	cin>>received;
	
	cout<<"Block size: ";
	cin>>blockSize;
	
	if(!sameLength(sent, received)){
		cout<<"Data does not have the same length"<<endl;
	}
	
	checkSum = getBlocks(sent, sentBlocks, blockSize);
	complement = onesComplement(checkSum);
	
	receivedValidate = getBlocks(received, receivedBlocks, blockSize);
	validation = validate(receivedValidate, complement);
	
	validation
	? cout<<"No error detected"
	: cout<<"Error detected";
	
	return 0;
}

/*
 * break string into k blocks with
 * blockSize number of bits
 */
string getBlocks(string data, string blocks[], int blockSize){
	int strLen = data.length();
	int numZeroes = strLen % blockSize;
	int startPos = 0;
	string sum = "";
	int blockLen = strLen / blockSize;
	
	/*
	 * append zeroes to the left of the data
	 * to fill in the gaps in a block
	 */
	if(numZeroes != 0){
		for(int i = 0;i < numZeroes;i++){
			data.insert(0, "0");
		}
		blockLen++;
	}
	
	/* 
	 * taking substring of original string
	 * to create the blocks of data
	 */
	for(int i = 0; startPos < strLen ;i++){
		blocks[i] = data.substr(startPos, blockSize);
		startPos += blockSize;
	}
	
	/*
	 * appending zeroes to the sum
	 * for its first use
	 */
	for(int i = 0;i < blockSize;i++){
		sum.insert(0, "0");
	}
	
	/*
	 * adding the blocks
	 */
	for(int i = 0;i < blockLen;i++){
		sum = addBlocks(blocks[i], sum);
	}
	
	return sum;
}

/*
 * adding the blocks of data
 */
string addBlocks(string add1, string add2){
	string result = "";
	string carry = "0";
	int strLen = add1.length();
	
	for(int i = strLen - 1;i >= 0;i--){
		if(add1[i] != add2[i]){
			if(carry == "0"){
				result.insert(0, "1");
			} else{
				result.insert(0, "0");
				carry = "1";
			}
		} else if(add1[i] == '0'){
			carry == "0"
			? result.insert(0, "0")
			: result.insert(0, "1");
			carry = "0";
		} else{
			carry == "0"
			? result.insert(0, "0")
			: result.insert(0, "1");
			carry = "1";
		}
	}
	
	/*
	 * if the resulting sum has a carry,
	 * recursion occurs to add the carry
	 * to the latest sum
	 */
	if(carry == "1"){
		for(int i = 0;i < strLen-1;i++){
			carry.insert(0, "0");
		}
		result = addBlocks(result, carry);
	}
	
	return result;
}

/*
 * performing 1s complement to the sum
 */
string onesComplement(string sum){
	for(int i = 0;i < sum.length();i++){
		sum[i] == '0'
		? sum[i] = '1'
		: sum[i] = '0';
	}
	
	return sum;
}

/*
 * validating via addition of the received data
 * blocks sum and the complement
 * if a zero is detected in the string
 * the function returns false 
 * else it returns true
 */
bool validate(string recSum, string complement){
	string result = addBlocks(recSum, complement);
	
	for(int i = 0;i < result.length();i++){
		if(result[i] == '0'){
			return false;
		}
	}
	
	return true;
}

/*
 * checking the length of sent and received data
 * strings if they are the same
 */
bool sameLength(string sent, string received){
	if(sent.length() == received.length()){
		return true;
	}
	return false;
}
