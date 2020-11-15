#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

int ConvertCharToInt(char m) { return (int)(m - 48); }

int Find_Real_Index(char *m) {
  int index = 0;
  while (m[index + 1] >= '0' && m[index + 1] <= '9')
    index++;
  return index;
}

bool Compare(int *a, int *b) {
  int i = 0;
  while (a[i] == b[i] & i < 50)
    i++;
  if (a[i] >= b[i])
    return true;
  else
    return false;
}

int *DivisionAlgorithm(int *a, int *b, int length) {
  int *c = new int[length];
  bool remember = false;
  for (int i = length - 1; i >= 0; i--) {
    c[i] = a[i] - b[i];
    if (remember == true)
      c[i]--;
    if (c[i] < 0) {
      c[i] += 10;
      remember = true;
    } else
      remember = false;
  }
  return c;
}

int main() {
  char a0[52], b0[52];
  ifstream file;
  file.open("Lab1.txt", ios::in);
  file >> a0 >> b0;
  
  file.close();
  int index_a = Find_Real_Index(a0);
  int index_b = Find_Real_Index(b0);

  int max_index = index_a > index_b ? index_a : index_b;
  int *a = new int[max_index];
  int *b = new int[max_index];

  for (int i = max_index - 1; i >= max_index - index_a; i--)
    a[i] = ConvertCharToInt(a0[i - max_index + index_a + 1]);

  for (int i = max_index - 1; i >= max_index - index_b; i--)
    b[i] = ConvertCharToInt(b0[i - max_index + index_b + 1]);

  cout << "Number 1 = " << a0[0];
  for (int i = 0; i < max_index; i++)
    cout << a[i];
  cout << endl;
  cout << "Number 2 = " << b0[0];
  for (int i = 0; i < max_index; i++)
    cout << b[i];
  cout << endl;

  bool check = true;
  if (Compare(a, b) == true)
    check = true; // a>b
  else
    check = false; // b>a

  int quotient = 0;
  if (check == true) {
    while (Compare(a, b)) {
      a = DivisionAlgorithm(a, b, max_index);
      quotient++;
    }
  } else {
    while (Compare(b, a)) {
      b = DivisionAlgorithm(b, a, max_index);
      quotient++;
    }
  }

  char sign = 0;
  if (a0[0] == b0[0])
    sign = '+';
  else
    sign = '-';

  cout << "\nQuotient = " << sign << quotient << endl;

  delete[] a;
  delete[] b;
  return 0;
}
