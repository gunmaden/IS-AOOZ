SELECT DISTINCT
  tes."testName",
  string_agg(DISTINCT task."studGroupName", ',')
FROM "Task" AS task
  INNER JOIN "Test" tes ON tes."testID" = task."testID"
WHERE task."studGroupName" IN (SELECT stg."studGroupName"
                               FROM "StudGroup" stg, "Decane" d
                               WHERE (d."facultyName" = stg."facultyName" AND
                                      d."decaneName" = 'Козлов Вячеслав Васильевич'))
GROUP BY tes."testName";


SELECT count(*) FROM (SELECT DISTINCT task."studGroupName", tes."testName", RANK() OVER(ORDER BY "testName") rnk
FROM "Task" AS task
INNER JOIN "Test" tes ON tes."testID" = task."testID"
WHERE task."studGroupName" IN ('ГИП-115а', 'ГИП-115б', 'ГИП-110')
GROUP BY task."studGroupName", tes."testName") as ttt;


SELECT COUNT(*) FROM (SELECT  column_name FROM table_name) AS temp;


WITH q AS (SELECT DISTINCT
             task."studGroupName",
             tes."testName"
           FROM "Task" AS task
             INNER JOIN "Test" tes ON tes."testID" = task."testID"
           WHERE task."studGroupName" IN (SELECT stg."studGroupName"
                                          FROM "StudGroup" stg, "Decane" d
                                          WHERE (d."facultyName" = stg."facultyName" AND
                                                 d."decaneName" = 'Козлов Вячеслав Васильевич'))
           GROUP BY task."studGroupName", tes."testName")

SELECT
  q."studGroupName",
  string_agg(q."testName", ','),
  count(SELECT * FROM q where q."testName"=q."testName")
FROM q
WHERE q."testName" IN ((SELECT DISTINCT q."testName"
                       FROM q
                       WHERE q."studGroupName" IN ('ГИП-110')))
GROUP BY q."studGroupName";



-- GROUP BY q."studGroupName"
-- WHERE ttt."studGroupName"!='ГИП-110'

SELECT ttt."testName" FROM (
SELECT DISTINCT task."studGroupName", tes."testName", RANK() OVER(ORDER BY "testName") rnk
FROM "Task" AS task
INNER JOIN "Test" tes ON tes."testID" = task."testID"
WHERE task."studGroupName" IN ('ГИП-115а', 'ГИП-115б', 'ГИП-110')
GROUP BY task."studGroupName", tes."testName")  AS ttt



SELECT * OVER(PARTITION BY col1,col2) AS cnt FROM table1


SELECT ttt."testName", string_agg(ttt."studGroupName",',') FROM (
SELECT DISTINCT task."studGroupName", tes."testName"
FROM "Task" AS task
INNER JOIN "Test" tes ON tes."testID" = task."testID"
WHERE task."studGroupName" IN ('ГИП-115а', 'ГИП-115б', 'ГИП-110')
GROUP BY task."studGroupName", tes."testName") as ttt
GROUP BY ttt."testName";


SELECT
  task."taskMark100",
  (task."taskReceive" - task."taskSend") AS elapsed,
  tes."testName",
  task."studName"
FROM "Task" AS task
  INNER JOIN "Test" tes ON tes."testID" = task."testID"
WHERE task."studGroupName" IN ('ГИП-112', 'ГИП-113')

SELECT
  t."testID",
  t."taskReceive",
  t."facultyName",
  test."testName",
  t."studName"
FROM "Task" t INNER JOIN "Test" test ON t."testID" = test."testID"
WHERE "studGroupName" = 'ГИП-110';

SELECT DISTINCT t."studGroupName"
FROM "Task" t
WHERE t."studGroupName" IN (SELECT stg."studGroupName"
                            FROM "StudGroup" stg
                            WHERE (stg."facultyName" = 'ФИСТ'));

SELECT DISTINCT t."studGroupName"
FROM "Task" t
WHERE t."studGroupName" IN (SELECT stg."studGroupName"
                            FROM "StudGroup" stg, "Decane" d
                            WHERE
                              (d."facultyName" = stg."facultyName" AND d."decaneName" = 'Козлов Вячеслав Васильевич'))

SELECT s."studGroupName"
FROM "StudGroup" s, "Decane" d
WHERE (d."facultyName" = s."facultyName" AND d."decaneName" = '')