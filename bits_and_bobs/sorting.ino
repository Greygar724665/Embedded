// Sort n items
void printList(float l[], int size) {
  int smin1 = size-1;
  Serial.print("[");
  for (int i = 0; i < size; i++) {
    Serial.print(l[i]);
    if (i < smin1) Serial.print(", ");
  }
  Serial.print("]");
}

void moveElements(float l[], int size, int from, int to) {
  // If you're moving an item outside of the list, or moving an item to outside of the list, return
  if (from == to || from < 0 || to < 0 || from >= size || to >= size) return;

  // Store item you're moving.
  float temp = l[from];
  if (from < to) {
    for (int k = from; k < to; k++) {
      l[k] = l[k+1];
    }
  } else {
    for (int k = from; k > to; k--) {
      l[k] = l[k-1];
    }
  }
  l[to] = temp;
}


void insertionSort(float l[], int size) {
  for (int i = 0; i < size-1; i++) {
    // Serial.print("Idx:");
    // Serial.print(i);
    // Serial.println(" ");
    float key = l[i+1];
    if (key < l[i]) {
      // Serial.print(key);
      // Serial.print(" is smaller than ");
      // Serial.print(l[i]);
      // Serial.println("\nStarting position search...");
      // Reverse search for where the key fits.
      for (int j = i; j >= 0; j--) {
        // Serial.print("\nCurrent reverse idx: ");
        // Serial.print(j);
        if (key > l[j]) {
          // Serial.println(String("\nPutting ")+key+String(" at index ")+j);
          moveElements(l, size, i+1, j+1);
          break;
        }
        if (j == 0) moveElements(l, size, i+1, 0);
      }
    }
  }
}

// Test sorting
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  delay(125);
	// GIVE SIZE OF ARRAY, REQUIRED
  float arr[14] = {12, 11, 13, 5, 6, 2, 9, 3, 4, 1, 0, 10, 8, 7};
	// GIVE SIZE OF ARRAY, REQUIRED
  printList(arr, 14);
  Serial.println("\n");
	// Time sorting
  unsigned long t0 = millis();
	// GIVE SIZE OF ARRAY, REQUIRED
  insertionSort(arr, 14);
  unsigned long t1 = millis();
	// GIVE SIZE OF ARRAY, REQUIRED
  printList(arr, 14);
  Serial.print("\nSorting took: ");
  Serial.print(t1-t0);
  Serial.print("ms");
}

void loop() {
  // put your main code here, to run repeatedly:

}
