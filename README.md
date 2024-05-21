# מטלה 2 - גרפים והעמסת אופרטורים

במטלה הקודמת מימשתם את המחלקה `Graph.cpp` המאפשרת ייצוג של גרפים בעזרת מטריצת שכנויות. במטלה הזאת, אתם תרחיבו את המחלקה ותוסיפו תמיכה באופרטורים חשבוניים על גרפים.
כאמור, הגרפים מיוצגים בעזרת מטריצת שכנויות, לכן כל האופרטורים צריכים להיות חוקיים עבור מטריצות.

אתם תצטרכו להוסיף את האופרטורים הבאים:

- שישה אופרטורים חשבוניים: חיבור (+) הוספה (+=) פלוס אונרי (+), ושלושת האופרטורים המקבילים לחיסור (-). כאמור, חיבור/חיסור של שתי מטריצות מוגדר רק על מטריצות מאותו סדר גודל nXn. ניסיון לחבר/לחסר שתי מטריצות שלא מקיימות תנאי זה יגרום לזריקת שגיאה.
- שישה אופרטורי השוואה: גדול, גדול-או-שווה, קטן, קטן-או-שווה, שווה, לא-שווה. לשם מטלה זו כללי השוואת גרפים הם כדלקמן:

  1. גרפים G1 ו-G2 ייקראו שווים אם הם מאותו סדר גודל ומכילים את אותן הצלעות (והמשקלים של הצלעות זהים) או אם G1 לא גדול מ-G2 וגם G2 לא גדול מ-G1.
  2. גרף G2 גדול מגרף G1 אם הגרף G1 מוכל ממש בגרף G2. אם אף גרף לא מוכל ממש בשני והגרפים לא שווים, אז גרף G2 גדול מגרף G1 אם מספר הצלעות ב-G2 גדול ממספר הצלעות ב-G1. אם בכל זאת מספר הצלעות זהה, אז הגרף G2 גדול מהגרף G1 אם המטריצה המייצגת של G2 בעלת סדר גודל גבוה יותר משל G1.
 הנחתי כי גרף מוכל אחד בשני גם אם המשקלים של הצלעות שונים.

- הגדלה ב-1 (++) והקטנה ב-1 (--) לפני ואחרי המספר. פעולה זו תגדיל או תקטין ב-1 את כל המשקלים של הצלעות בגרף.
(אם לצלע לא הייתה קיימת,כלומר משקל 0 לא נוסיף ולא נוריד מהצלע)

- הכפלה בסקלר שלם (`int`) - מכפיל את המשקל של כל הצלעות.
- הכפלת גרפים - אנחנו מגדירים את פעולת הכפל בין גרף G1 לגרף G2 על ידי מכפלה של המטריצות המייצגות של שני הגרפים. התוצאה צריכה להיות מטריצה המייצגת גרף. ניסיון לבצע כפל בין גרפים בגדלים שונים צריך לזרוק שגיאה.
(בסוף ההכפלה איפסתי את כל האלסון על מנת שלא יהיה צלע שמגיעה לעצמה)
- אופרטור פלט - הדפסה הגיונית של הגרף (צורת ההפדסה היא לשיקולכם).


