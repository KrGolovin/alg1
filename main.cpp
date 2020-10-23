#include <iostream>
#include <vector>
#include <random>

#define leftIndexOfSection result.first
#define rightIndexOfSection result.second

void print(std::vector<int> &array)
{
  for (int element : array)
  {
    std::cout << element << ' ';
  }
  std::cout << std::endl;
}

int getRandomIndex(int leftBoarder, int rightBoarder)
{
  std::random_device randomDevice;
  std::default_random_engine generator(randomDevice());
  std::uniform_int_distribution<int> distribution(leftBoarder,rightBoarder);
  return distribution(generator);
}

std::pair<int, int> partition(std::vector<int> &array, int leftBoarder, int rightBoarder, int section)
{
  int sectionElement = array[section];
  int leftIterator = leftBoarder;
  int rightIterator = rightBoarder;
  while (leftIterator <= rightIterator)
  {
    while (array[leftIterator] < sectionElement)
    {
      leftIterator++;
    }
    while (array[rightIterator] > sectionElement)
    {
      rightIterator--;
    }
    if ((rightIterator == leftIterator) && (array[leftIterator] == sectionElement))
    {
      return std::make_pair(rightIterator, leftIterator);
    }
    if ((array[rightIterator] == array[leftIterator]) && (array[leftIterator] == sectionElement))
    {
      std::pair<int, int> result = partition(array, leftIterator + 1, rightIterator - 1, leftIterator);
      if ((array[leftIndexOfSection] != sectionElement) || (array[rightIndexOfSection] != sectionElement))
      {
        std::swap(array[leftIterator], array[leftIndexOfSection]);
        std::swap(array[rightIterator], array[rightIndexOfSection]);
      }
      else
      {
        if (leftIterator != leftIndexOfSection) {
          std::swap(array[leftIterator], array[--leftIndexOfSection]);
        }
        if (rightIterator != rightIndexOfSection) {
          std::swap(array[rightIterator], array[++rightIndexOfSection]);
        }
      }
      return std::make_pair(leftIndexOfSection, rightIndexOfSection);
    }
    if (leftIterator < rightIterator) {
      std::swap(array[leftIterator], array[rightIterator]);
    }
  }
  return std::make_pair(rightIterator, leftIterator);
}

int select(std::vector<int> &array, int leftBorder, int rightBorder , int k)
{
  int randomIndex = getRandomIndex(0, array.size() - 1);
  std::pair<int, int> result = partition(array, leftBorder, rightBorder, randomIndex);
  if (k < leftIndexOfSection)
  {
    return select(array, leftBorder, leftIndexOfSection - 1, k);
  }
  if (k < rightIndexOfSection)
  {
    return array[leftIndexOfSection];
  }
  return select(array, rightIndexOfSection + 1, rightBorder, k);
}

int main()
{
  int n = 0;
  std::cin >> n;
  std::vector<int> array(n);
  for (int &element : array)
  {
    std::cin >> element;
  }
  int indexOfSection = 0;
  std::cin >> indexOfSection;
  std::pair<int, int> result = partition(array, 0, array.size() - 1, indexOfSection);
  print(array);
  std::cout << leftIndexOfSection << ' ' << rightIndexOfSection << std::endl;
  std::cout << "median: ";
  std::cout << select(array, 0, array.size() - 1, (array.size() - 1) / 2);
  return 0;
}
