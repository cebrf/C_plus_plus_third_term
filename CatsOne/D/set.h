class Set {
 public:
  Set() : data(), size(0) {}
  explicit Set(const std::vector<int64_t>& data) : data(), size(0) {
    for (int i = 0; i < data.size(); i++) {
      if (this->size == 0 || 
          this->data[this->size - 1] != data[i]) {
        this->data.push_back(data[i]);
        this->size++;
      }
    }
  }
  std::vector<int64_t> Data() const {
    return this->data;
  }
  bool Contains(int64_t el) const {
    for (int i = 0; i < this->size; i++) {
      if (this->data[i] == el) {
        return true;
      }
    }
    return false;
  }
  void Add(int64_t el) {
    if (!this->Contains(el)) {
      std::vector<int64_t>::iterator iter;
      for (iter = this->data.begin(); 
          iter < this->data.end(); iter++) {
        if (*iter > el) {
          if (iter != this->data.begin()) {
            iter--;
          }
          this->data.insert(iter, el);
          break;
        }
      }
      iter = this->data.begin();
      this->data.insert(iter, el);
      this->size++;
    }
  }
  void Remove(int64_t el) {
    if (this->Contains(el)) {
      std::vector<int64_t>::iterator iter;
      for (iter = this->data.begin(); 
          iter < this->data.end(); iter++) {
        if (*iter == el) {
          break;
        }
      }
      this->data.erase(iter);
      this->size--;
    }
  }
  Set Union(const Set& rhs) {
    int i = 0, j = 0, k = 0;
    Set new_set;
    while (i < this->size && j < rhs.size) {
      if (this->data[i] < rhs.data[j]) {
        if (k == 0 || new_set.data[k - 1] != this->data[i]) {
          new_set.data.push_back(this->data[i]);
          k++;
        }
        i++;
      } else {
        if (k == 0 || new_set.data[k - 1] != rhs.data[j]) {
          new_set.data.push_back(rhs.data[j]);
          k++;
        }
        j++;
      }
    }
    while (i < this->size) {
      if (k == 0 || new_set.data[k - 1] != this->data[i]) {
        new_set.data.push_back(this->data[i]);
        k++;
      }
      i++;
    }
    while (j < rhs.size) {
      if (k == 0 || new_set.data[k - 1] != rhs.data[j]) {
        new_set.data.push_back(rhs.data[j]);
        k++;
      }
      j++;
    }
    return new_set;
  }
  Set Intersection(const Set& rhs) const {
    Set new_set;
    int i = 0, j = 0, k = 0;
    while (i < this->size && j < rhs.size) {
      if (this->data[i] == rhs.data[j]) {
        if (k == 0 || new_set.data[k - 1] != rhs.data[j]) {
          new_set.data.push_back(rhs.data[j]);
          k++;
        }
        i++;
        j++;
      } else if(this->data[i] < rhs.data[j]) {
        i++;
      } else {
        j++;
      }
    }
    return new_set;
  }
  Set Difference(const Set& rhs) const {
    Set new_set;
    for (int i = 0; i < this->size; i++) {
      if (!rhs.Contains(this->data[i])) {
        new_set.data.push_back(this->data[i]);
        new_set.size++;
      }
    }
    return new_set;
  }
  Set SymmetricDifference(const Set& rhs) const {
    Set new_set;
    for (int i = 0; i < this->size; i++) {
      if (!rhs.Contains(this->data[i])) {
        new_set.data.push_back(this->data[i]);
        new_set.size++;
      }
    }
    for (int j = 0; j < rhs.size; j++) {
      if (!this->Contains(rhs.data[j])) {
        new_set.data.push_back(rhs.data[j]);
        new_set.size++;
      }
    }
    return new_set;
  }

 private:
  std::vector<int64_t> data;
  size_t size;
};
