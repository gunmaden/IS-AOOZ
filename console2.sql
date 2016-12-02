WITH need_groups as (SELECT DISTINCT "studGroupName"
                     FROM "StudGroup" sg, "Decane" d
                     WHERE (sg."facultyName"=d."facultyName" AND d."decaneName"='Козлов Вячеслав Васильевич')),
total_groups as (SELECT DISTINCT task."studGroupName"
FROM "Task" task, need_groups
WHERE task."studGroupName" IN (need_groups."studGroupName"))
SELECT * FROM total_groups;



SELECT * FROM "Task" WHERE "studGroupName"='ГИП-110';

SELECT DISTINCT t."studGroupName"
                        FROM "Task" t
                         WHERE t."studGroupName" IN (
                         SELECT stg."studGroupName" from "StudGroup" stg, "Decane" d
                         WHERE (d."facultyName" = stg."facultyName" AND d."decaneName" = 'Козлов Вячеслав Васильевич'));

-- get
WITH q AS (SELECT DISTINCT
             task."studGroupName",
             tes."testName"
           FROM "Task" AS task, "Test" tes WHERE tes."testID" = task."testID" and
           task."studGroupName" IN (SELECT stg."studGroupName"
                                          FROM "StudGroup" stg, "Decane" d
                                          WHERE (d."facultyName" = stg."facultyName" AND
                                                 d."decaneName" = 'Козлов Вячеслав Васильевич'))
           GROUP BY task."studGroupName", tes."testName"),
  count_filters as (SELECT count(*) as count_fil FROM (VALUES (0),(1),(2))  as count_fil(q1)),
  filters_group as (SELECT * FROM (VALUES ('ГИП-115б'),('ГИП-114'),('ГИП-115а')) as gr_fil(gr_fil))
SELECT
--   q."studGroupName",
  q."testName"
FROM q, filters_group, count_filters
WHERE q."studGroupName" in (filters_group.gr_fil)
GROUP BY q."testName", count_fil
HAVING count(q."studGroupName")=count_filters.count_fil;

