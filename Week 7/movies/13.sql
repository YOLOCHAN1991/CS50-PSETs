SELECT DISTINCT people.name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE NOT people.name = "Kevin Bacon"
AND title IN (SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = 'Kevin Bacon' AND birth = 1958);