/* 
Justin Isaraphanich
 COP 3014 
 Assignment 2: Loan Calculator 
 6/12/2023
*/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//function calls
double calculate_amortization(double P, double r, int n);
void calculate_monthly_and_balance(double& interest, double& principal, double& balance, double r, double M);
void calculate_totals(double& total_payments, double& total_interest, double M, double& interest);
void get_inputs(double& P, double& r, int& n);
void output(ofstream& outfile, double M, int n, double total_payments, double total_interest);

int main() {
	double P, r, M, balance, interest, principal, total_payments = 0, total_interest = 0;
	int n;
	char repeat;
	ofstream outfile("loan_report.txt"); //opens file for editing
	cout << fixed << setprecision(2); //ensures correct decimal rounding
	outfile << fixed << setprecision(2);
	
	do {
		get_inputs(P, r, n);
		M = calculate_amortization(P, r, n);
		balance = P;

		for (int month = 1; month <= n; month++) { 
			calculate_monthly_and_balance(interest, principal, balance, r, M);
			calculate_totals(total_payments, total_interest, M, interest);
			cout << "Month " << month << " Payment: $" << M << " Interest: $" << interest << " Principal: $" << principal << " Balance: $" << balance << endl;
			outfile << "Month " << month << " Payment: $" << M << " Interest: $" << interest << " Principal: $" << principal << " Balance: $" << balance << endl;
		} 

		output(outfile, M , n, total_payments, total_interest);

		cout << "Would you like to calculate another loan? (Y/N): "; //allows program to be repeated
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');
	
	outfile.close(); //closes file 

	return 0;
}

//function definitions
double calculate_amortization(double P, double r, int n) {
	double
	M = P * (r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
	return M;
}
void calculate_monthly_and_balance(double& interest, double& principal, double& balance, double r, double M) {
	interest = r * balance;
	principal = M - interest;
	balance -= principal;
	if (abs(balance) < 0.01) { //ensures balance 0's out when outputted
		balance = 0;
	}
}
void calculate_totals(double& total_payments, double& total_interest, double M, double& interest) {
	total_payments += M;
	total_interest += interest;
}
void get_inputs(double& P, double& r, int& n) {
	while (true) {
		cout << "Enter the principal loan amount (positive value): ";
		cin >> P;
		if (cin.fail() || P <= 0) {
			cin.clear();  // clears fail state
			cout << "Invalid input. Please enter a positive number." << endl;
			exit(1);
		}
		else {
			break;  // exit the loop if input is valid
		}
	}

	while (true) {
		cout << "Enter the annual interest rate (in decimal, e.g., 0.1 for 10%): ";
		cin >> r;
		if (cin.fail() || r <= 0 || r >= 1) {
			cin.clear();
			cout << "Invalid input. Please enter a number between 0 and 1." << endl;
			exit(1);
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "Enter the loan period in years (positive integer): ";
		cin >> n;
		if (cin.fail() || n <= 0) {
			cin.clear();
			cout << "Invalid input. Please enter a positive integer." << endl;
			exit(1);
		}
		else {
			break;
		}
	}

	r /= 12; //makes r a decimal equal for each month
	n *= 12; // makes n equal to months in loan
}
void output(ofstream& outfile, double M, int n, double total_payments, double total_interest) {
	

	cout << "Payment Every Month: $" << M << endl;
	cout << "Total of " << n << " Payments: $" << total_payments << endl;
	cout << "Total Interest: $" << total_interest << endl;

	
	outfile << "Payment Every Month: $" << M << endl;
	outfile << "Total of " << n << " Payments: $" << total_payments << endl;
	outfile << "Total Interest: $" << total_interest << endl;
}