#include <string>
#include <vector>
class Date {
 public:
  Date(int year, int month, int day) :
    year(year), month(month), day(day) {}
  bool IsLeap() const {
    if ((year % 4 == 0 && year % 100 != 0)
      || (year % 400 == 0)) {
      return 1;
    } else {
        return 0;
    }
  }
  std::string ToString() const {
    std::string day_s, month_s, year_s;
    if (year < 10)
      year_s = "000" + std::to_string(year);
    else if (year < 100)
      year_s = "00" + std::to_string(year);
    else if (year < 1000)
      year_s = "0" + std::to_string(year);
    else
      year_s = std::to_string(year);
    if (month < 10)
      month_s = "0" + std::to_string(month);
    else
      month_s = std::to_string(month);
    if (day < 10)
      day_s = "0" + std::to_string(day);
    else
      day_s = std::to_string(day);
    return day_s + "." + month_s + "." + year_s;
  }
  Date DaysLater(int days) {
    Date res(this->year, this->month, this->day);
    while (1) {
      if (days >= 365 && !res.IsLeap()) {
        res.year++;
        days -= 365;
      } else if (days >= 366 && res.IsLeap()) {
        res.year++;
        days -= 366;
      } else {
        break;
      }
    }
    while (days > 0 && res.day != 1) {
      days--;
      res.day++;
      if (res.day == days_in_month[res.month]) {
        if (res.month == 2 && res.IsLeap()
            && res.day - 1 < days_in_month[res.month])
          continue;
        res.month++;
        res.day = 1;
      }
    }
    while (1) {
      if (days_in_month[res.month] < days) {
        if (res.month == 2 && res.IsLeap()
            && days_in_month[res.month] + 1 >= days)
          days--;
        days -= days_in_month[res.month];
        res.month++;
        if (res.month > 12) {
          res.year++;
          res.month = 1;
        } else {
          break;
        }
      } else {
        break;
      }
    }
    res.day += days;
    if (res.day > days_in_month[res.month]) {
      if (res.IsLeap() && res.month == 2) {
        if (res.day > days_in_month[res.month] + 1) {
          res.day -= days_in_month[res.month++] + 1;
        } else { }
      } else {
        res.day -= days_in_month[res.month++];
      }
    }
    return res;
  }
  int DaysLeft(const Date& date) const {
    int days = 0;
    Date current_date(year, month, day);
    while (!(day == date.day && month == date.month && year == date.year)
        && day != 1) {
      days++;
      current_date.day++;
      if (current_date.day == days_in_month[current_date.month]) {
        if (current_date.month == 2 && current_date.IsLeap()
            && current_date.day - 1 < days_in_month[current_date.month])
          continue;
        current_date.month++;
        if (current_date.month == 13) {
          current_date.year++;
          current_date.month = 1;
        }
        current_date.day = 1;
      }
    }
    while (!(current_date.month == date.month
        && current_date.year == date.year)) {
      days += days_in_month[current_date.month];
      if (current_date.month == 2 && current_date.IsLeap())
        days++;
      current_date.month++;
      if (current_date.month == 13) {
        current_date.year++;
        current_date.month = 1;
      }
    }
    days += date.day - current_date.day;
    return days;
  }
  int year, month, day;
  std::vector<int> days_in_month =
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};
