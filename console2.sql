WITH need_groups AS (SELECT DISTINCT "studGroupName"
                     FROM "StudGroup" sg, "Decane" d
                     WHERE (sg."facultyName" = d."facultyName" AND d."decaneName" = 'Козлов Вячеслав Васильевич')),
    total_groups AS (SELECT DISTINCT task."studGroupName"
                     FROM "Task" task, need_groups
                     WHERE task."studGroupName" IN (need_groups."studGroupName"))
SELECT *
FROM total_groups;


SELECT *
FROM "Task"
WHERE "studGroupName" = 'ГИП-110';

SELECT DISTINCT t."studGroupName"
FROM "Task" t
WHERE t."studGroupName" IN (
  SELECT stg."studGroupName"
  FROM "StudGroup" stg, "Decane" d
  WHERE (d."facultyName" = stg."facultyName" AND d."decaneName" = 'Козлов Вячеслав Васильевич'));

-- get
WITH q AS (SELECT DISTINCT
             task."studGroupName",
             tes."testName"
           FROM "Task" AS task, "Test" tes
           WHERE tes."testID" = task."testID" AND
                 task."studGroupName" IN (SELECT stg."studGroupName"
                                          FROM "StudGroup" stg, "Decane" d
                                          WHERE (d."facultyName" = stg."facultyName" AND
                                                 d."decaneName" = 'Козлов Вячеслав Васильевич'))
           GROUP BY task."studGroupName", tes."testName"),
    count_filters AS (SELECT 3 cof),
    filters_group AS (SELECT *
                      FROM (VALUES ('ГИП-113'), ('ГИП-114'), ('ГИП-115а')) AS gr_fil(gr_fil))
SELECT q."testName"
FROM q, filters_group, count_filters
WHERE q."studGroupName" IN (filters_group.gr_fil)
GROUP BY q."testName", cof
HAVING count(q."studGroupName") = count_filters.cof;

SELECT *
FROM "Task"

SELECT DISTINCT st."studNameFirst"
FROM "Stud" st, "StudGroup" sg
WHERE (st."old_studGroupID" = sg."studGroupID" AND sg."studGroupName" IN ('ГИП-112', 'ГИП-114'))


SELECT
  tes."testName",
  round(avg(t."taskMark100"))
FROM "Task" t
  JOIN "Test" tes ON t."testID" = tes."testID"
WHERE t."studName" = 'Андреев Николай Валерьевич'
GROUP BY tes."testName"