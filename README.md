# CSVcat
#### General
This Program allows you to print formatted data in CSV format into the console. Designed to print MS Excel tables saved as .csv files.  

#### How to use:
After downloading the binaries (or building it by youself using **make**) launch **csvcat** file. Use the following command:
```
./csvcat <path to file>.
```
You can use prepared samples to test the program. 

#### Examples:
##### 1) OutputOverloadSample1.csv
Command:
```
./csvcat ../CSVcat/samples/OutputOverloadSample1.csv
```
Output:
```
+---+------------------+---------+---+----------------------+
| 1 | 2                | 3       |   |                      |
+---+------------------+---------+---+----------------------+
| a | ,                | c       |   | qwertyuiopasdfghjklz |
|   |                  |         |   | xcvbnmqwertyuioasdfg |
|   |                  |         |   | hjkzxcvbn            |
+---+------------------+---------+---+----------------------+
| 3 | abcdefghijklmnop | 8       |   |                      |
+---+------------------+---------+---+----------------------+
| " | ""               | "hello" | \ |                      |
+---+------------------+---------+---+----------------------+
|   | ","              | .       | / |                      |
+---+------------------+---------+---+----------------------+
```
##### 2) RegularSample1.csv
Command:
```
./csvcat ../CSVcat/samples/RegularSample1.csv   
```
Output:
```
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
| basis | x0    | x1    | x2    | x3   | x4   | x5    | min |                      |
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
| x3    | 3     | -1    | 1     | 1    | 0    | 0     | -3  |                      |
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
| x4    | 42    | 6     | 7     | 0    | 1    | 0     | 7   |                      |
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
| x5    | 6     | 2     | 3     | 0    | 0    | 1     | 3   | +I*0.5; +II*-3; +III |
|       |       |       |       |      |      |       |     | *1;                  |
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
|       | 0     | -2.00 | 1     | 0    | 0    | 0     | 0   |                      |
+-------+-------+-------+-------+------+------+-------+-----+----------------------+
                                        ...
```

# CSVstud
#### General
Implementation of the task in the **docs** dir.

#### How to use:
After downloading the binaries (or building it by youself) launch **csvstud** file. Use the following command:
```
./csvstud <path to file>.
```
You can use prepared samples to test the program. 

#### Examples:
##### 1) StudentSample1.csv
Command:
```
./csvstud ../CSVstud/samples/StudentSample1.csv
```
Output:
```
+-----------+-------------+-----------+--------------+----------+
| Succeeded | Name        | Surname   | Average mark | Attended |
+-----------+-------------+-----------+--------------+----------+
|           | Elli        | Mansell   | 3.94         | 0        |
+-----------+-------------+-----------+--------------+----------+
| +         | Mariana     | Rosales   | 4.08         | 19       |
+-----------+-------------+-----------+--------------+----------+
|           | Callam      | Lozano    | 2.92         | 13       |
+-----------+-------------+-----------+--------------+----------+
|           | Lachlan     | Markham   | 3.32         | 3        |
+-----------+-------------+-----------+--------------+----------+
|           | Sophia-Rose | Medina    | 3.76         | 5        |
+-----------+-------------+-----------+--------------+----------+
| +         | Josh        | Young     | 4.45         | 12       |
+-----------+-------------+-----------+--------------+----------+
|           | Rodrigo     | Alston    | 4.66         | 3        |
+-----------+-------------+-----------+--------------+----------+
| +         | Efa         | Luna      | 4.92         | 18       |
+-----------+-------------+-----------+--------------+----------+
                                ...
```
#### Known issues:
1) TablePrinter is not thread-safe
