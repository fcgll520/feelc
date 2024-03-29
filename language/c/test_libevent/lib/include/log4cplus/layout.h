// Module:  Log4CPLUS
// File:    Layout.h
// Created: 6/2001
// Author:  Tad E. Smith
//
//
// Copyright (C) Tad E. Smith  All rights reserved.
//
// This software is published under the terms of the Apache Software
// License version 1.1, a copy of which has been included with this
// distribution in the LICENSE.APL file.
//

/** @file */

#ifndef _LOG4CPLUS_LAYOUT_HEADER_
#define _LOG4CPLUS_LAYOUT_HEADER_

#include <log4cplus/config.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/streams.h>
#include <log4cplus/tstring.h>
#include <log4cplus/helpers/logloguser.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/helpers/timehelper.h>
#include <log4cplus/spi/loggingevent.h>

#include <vector>


namespace log4cplus
{

// Forward Declarations
namespace pattern
{
class PatternConverter;
}


/**
 * This class is used to layout strings sent to an {@link
 * #Appender}.
 */
class LOG4CPLUS_EXPORT Layout : protected :: log4cplus::helpers::LogLogUser
{
public:
    Layout() : llmCache(getLogLevelManager()) {}
    Layout(const log4cplus::helpers::Properties &)
        : llmCache(getLogLevelManager())  {}
    virtual ~Layout() {}

    virtual void formatAndAppend(log4cplus::tostream &output,
                                 const log4cplus::spi::InternalLoggingEvent &event) = 0;
protected:
    LogLevelManager &llmCache;

private:
    // Disable copy
    Layout(const Layout &);
    Layout &operator=(Layout &);
};



/**
 * SimpleLayout consists of the LogLevel of the log statement,
 * followed by " - " and then the log message itself. For example,
 *
 * <pre>
 *         DEBUG - Hello world
 * </pre>
 *
 * <p>
 *
 * <p>{@link PatternLayout} offers a much more powerful alternative.
 */
class LOG4CPLUS_EXPORT SimpleLayout : public Layout
{
public:
    SimpleLayout() {}
    SimpleLayout(const log4cplus::helpers::Properties &properties) : Layout(properties) {}

    virtual void formatAndAppend(log4cplus::tostream &output,
                                 const log4cplus::spi::InternalLoggingEvent &event);

private:
    // Disallow copying of instances of this class
    SimpleLayout(const SimpleLayout &);
    SimpleLayout &operator=(const SimpleLayout &);
};



/**
 * TTCC layout format consists of time, thread, Logger and nested
 * diagnostic context information, hence the name.
 *
 * <p>The time format depends on the <code>DateFormat</code> used.  Use the
 * <code>Use_gmtime</code> to specify whether messages should be logged using
 * <code>localtime</code> or <code>gmtime</code>.
 *
 * <p>Here is an example TTCCLayout output with the {@link RelativeTimeDateFormat}.
 *
 * <pre>
 * 176 [main] INFO  org.apache.log4j.examples.Sort - Populating an array of 2 elements in reverse order.
 * 225 [main] INFO  org.apache.log4j.examples.SortAlgo - Entered the sort method.
 * 262 [main] DEBUG org.apache.log4j.examples.SortAlgo.OUTER i=1 - Outer loop.
 * 276 [main] DEBUG org.apache.log4j.examples.SortAlgo.SWAP i=1 j=0 - Swapping intArray[0] = 1 and intArray[1] = 0
 * 290 [main] DEBUG org.apache.log4j.examples.SortAlgo.OUTER i=0 - Outer loop.
 * 304 [main] INFO  org.apache.log4j.examples.SortAlgo.DUMP - Dump of interger array:
 * 317 [main] INFO  org.apache.log4j.examples.SortAlgo.DUMP - Element [0] = 0
 * 331 [main] INFO  org.apache.log4j.examples.SortAlgo.DUMP - Element [1] = 1
 * 343 [main] INFO  org.apache.log4j.examples.Sort - The next log statement should be an error message.
 * 346 [main] ERROR org.apache.log4j.examples.SortAlgo.DUMP - Tried to dump an uninitialized array.
 * 467 [main] INFO  org.apache.log4j.examples.Sort - Exiting main method.
 * </pre>
 *
 *  <p>The first field is the number of milliseconds elapsed since the
 *  start of the program. The second field is the thread outputting the
 *  log statement. The third field is the LogLevel, the fourth field is
 *  the logger to which the statement belongs.
 *
 *  <p>The fifth field (just before the '-') is the nested diagnostic
 *  context.  Note the nested diagnostic context may be empty as in the
 *  first two statements. The text after the '-' is the message of the
 *  statement.
 *
 *  <p>PatternLayout offers a much more flexible alternative.
 */
class LOG4CPLUS_EXPORT TTCCLayout : public Layout
{
public:
    // Ctor and dtor
    TTCCLayout(bool use_gmtime = false);
    TTCCLayout(const log4cplus::helpers::Properties &properties);
    virtual ~TTCCLayout();

    virtual void formatAndAppend(log4cplus::tostream &output,
                                 const log4cplus::spi::InternalLoggingEvent &event);

protected:
    log4cplus::tstring dateFormat;
    bool use_gmtime;

private:
    // Disallow copying of instances of this class
    TTCCLayout(const TTCCLayout &);
    TTCCLayout &operator=(const TTCCLayout &);
};




/**
 * A flexible layout configurable with pattern string.
 *
 * <p>The goal of this class is to format a InternalLoggingEvent and return
 * the results as a string. The results depend on the <em>conversion
 * pattern</em>.
 *
 * <p>The conversion pattern is closely related to the conversion
 * pattern of the printf function in C. A conversion pattern is
 * composed of literal text and format control expressions called
 * <em>conversion specifiers</em>.
 *
 * <p><i>You are free to insert any literal text within the conversion
 * pattern.</i>
 *
 * <p>Each conversion specifier starts with a percent sign (%%) and is
 * followed by optional <em>format modifiers</em> and a <em>conversion
 * character</em>. The conversion character specifies the type of
 * data, e.g. Logger, LogLevel, date, thread name. The format
 * modifiers control such things as field width, padding, left and
 * right justification. The following is a simple example.
 *
 * <p>Let the conversion pattern be <b>"%-5p [%t]: %m%n"</b> and assume
 * that the log4cplus environment was set to use a PatternLayout. Then the
 * statements
 * <pre>
 * Logger root = Logger.getRoot();
 * LOG4CPLUS_DEBUG(root, "Message 1");
 * LOG4CPLUS_WARN(root, "Message 2");
 * </pre>
 * would yield the output
 * <pre>
 * DEBUG [main]: Message 1
 * WARN  [main]: Message 2
 * </pre>
 *
 * <p>Note that there is no explicit separator between text and
 * conversion specifiers. The pattern parser knows when it has reached
 * the end of a conversion specifier when it reads a conversion
 * character. In the example above the conversion specifier
 * <b>"%-5p"</b> means the LogLevel of the logging event should be left
 * justified to a width of five characters.
 *
 * The recognized conversion characters are
 *
 * <p>
 * <table border="1" CELLPADDING="8">
 * <tr>
 * <td>Conversion Character</td>
 * <td>Effect</td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>c</b></td>
 *
 *   <td>Used to output the logger of the logging event. The
 *   logger conversion specifier can be optionally followed by
 *   <em>precision specifier</em>, that is a decimal constant in
 *   brackets.
 *
 *   <p>If a precision specifier is given, then only the corresponding
 *   number of right most components of the logger name will be
 *   printed. By default the logger name is printed in full.
 *
 *   <p>For example, for the logger name "a.b.c" the pattern
 *   <b>%c{2}</b> will output "b.c".
 *
 * </td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>d</b></td>
 *
 *   <td>Used to output the date of the logging event in <b>localtime</b>.
 *
 *   <p>The date conversion specifier may be followed by a <em>date format
 *   specifier</em> enclosed between braces. For example, <b>%%d{%%H:%%M:%%s}</b>
 *   or <b>%%d{%%d&nbsp;%%b&nbsp;%%Y&nbsp;%%H:%%M:%%s}</b>.  If no date format
 *   specifier is given then <b>%%d{%%d&nbsp;%%m&nbsp;%%Y&nbsp;%%H:%%M:%%s}</b>
 *   is assumed.
 *
 *   <p>The Following format options are possible:
 *   <ul>
 *   <li>%%a -- Abbreviated weekday name</li>
 *   <li>%%A -- Full weekday name</li>
 *   <li>%%b -- Abbreviated month name</li>
 *   <li>%%B -- Full month name</li>
 *   <li>%%c -- Standard date and time string</li>
 *   <li>%%d -- Day of month as a decimal(1-31)</li>
 *   <li>%%H -- Hour(0-23)</li>
 *   <li>%%I -- Hour(1-12)</li>
 *   <li>%%j -- Day of year as a decimal(1-366)</li>
 *   <li>%%m -- Month as decimal(1-12)</li>
 *   <li>%%M -- Minute as decimal(0-59)</li>
 *   <li>%%p -- Locale's equivalent of AM or PM</li>
 *   <li>%%q -- milliseconds as decimal(0-999) -- <b>Log4CPLUS specific</b>
 *   <li>%%Q -- fractional milliseconds as decimal(0-999.999) -- <b>Log4CPLUS specific</b>
 *   <li>%%S -- Second as decimal(0-59)</li>
 *   <li>%%U -- Week of year, Sunday being first day(0-53)</li>
 *   <li>%%w -- Weekday as a decimal(0-6, Sunday being 0)</li>
 *   <li>%%W -- Week of year, Monday being first day(0-53)</li>
 *   <li>%%x -- Standard date string</li>
 *   <li>%%X -- Standard time string</li>
 *   <li>%%y -- Year in decimal without century(0-99)</li>
 *   <li>%%Y -- Year including century as decimal</li>
 *   <li>%%Z -- Time zone name</li>
 *   <li>%% -- The percent sign</li>
 *   </ul>
 *
 *   <p>Lookup the documentation for the <code>strftime()</code> function
 *   found in the <code>&lt;ctime&gt;</code> header for more information.
 * </td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>D</b></td>
 *
 *   <td>Used to output the date of the logging event in <b>Local</b> time.
 *
 *   <p>All of the above information applies.
 * </td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>F</b></td>
 *
 *   <td>Used to output the file name where the logging request was
 *   issued.
 *
 *   <p><b>NOTE</b> Unlike log4j, there is no performance penalty for
 *   calling this method.
 *
 * </tr>
 *
 * <tr>
 * <td align=center><b>l</b></td>
 *
 *   <td>Equivalent to using "%F:%L"
 *
 *   <p><b>NOTE:</b> Unlike log4j, there is no performance penalty for
 *   calling this method.
 *
 * </td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>L</b></td>
 *
 *   <td>Used to output the line number from where the logging request
 *   was issued.
 *
 *   <p><b>NOTE:</b> Unlike log4j, there is no performance penalty for
 *   calling this method.
 *
 * </tr>
 *
 *
 * <tr>
 *   <td align=center><b>m</b></td>
 *   <td>Used to output the application supplied message associated with
 *   the logging event.</td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>n</b></td>
 *
 *   <td>Outputs the platform dependent line separator character or
 *   characters.
 * </tr>
 *
 * <tr>
 *   <td align=center><b>p</b></td>
 *   <td>Used to output the LogLevel of the logging event.</td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>t</b></td>
 *
 *   <td>Used to output the name of the thread that generated the
 *   logging event.</td>
 * </tr>
 *
 * <tr>
 *
 *   <td align=center><b>x</b></td>
 *
 *   <td>Used to output the NDC (nested diagnostic context) associated
 *   with the thread that generated the logging event.
 *   </td>
 * </tr>
 *
 * <tr>
 *   <td align=center><b>"%%"</b></td>
 *   <td>The sequence "%%" outputs a single percent sign.
 *   </td>
 * </tr>
 *
 * </table>
 *
 * <p>By default the relevant information is output as is. However,
 * with the aid of format modifiers it is possible to change the
 * minimum field width, the maximum field width and justification.
 *
 * <p>The optional format modifier is placed between the percent sign
 * and the conversion character.
 *
 * <p>The first optional format modifier is the <em>left justification
 * flag</em> which is just the minus (-) character. Then comes the
 * optional <em>minimum field width</em> modifier. This is a decimal
 * constant that represents the minimum number of characters to
 * output. If the data item requires fewer characters, it is padded on
 * either the left or the right until the minimum width is
 * reached. The default is to pad on the left (right justify) but you
 * can specify right padding with the left justification flag. The
 * padding character is space. If the data item is larger than the
 * minimum field width, the field is expanded to accommodate the
 * data. The value is never truncated.
 *
 * <p>This behavior can be changed using the <em>maximum field
 * width</em> modifier which is designated by a period followed by a
 * decimal constant. If the data item is longer than the maximum
 * field, then the extra characters are removed from the
 * <em>beginning</em> of the data item and not from the end. For
 * example, it the maximum field width is eight and the data item is
 * ten characters long, then the first two characters of the data item
 * are dropped. This behavior deviates from the printf function in C
 * where truncation is done from the end.
 *
 * <p>Below are various format modifier examples for the logger
 * conversion specifier.
 *
 * <p>
 * <TABLE BORDER=1 CELLPADDING=8>
 * <tr>
 * <td>Format modifier</td>
 * <td>left justify</td>
 * <td>minimum width</td>
 * <td>maximum width</td>
 * <td>comment</td>
 * </tr>
 *
 * <tr>
 * <td align=center>%20c</td>
 * <td align=center>false</td>
 * <td align=center>20</td>
 * <td align=center>none</td>
 *
 * <td>Left pad with spaces if the logger name is less than 20
 * characters long.
 * </tr>
 *
 * <tr> <td align=center>%-20c</td> <td align=center>true</td> <td
 * align=center>20</td> <td align=center>none</td> <td>Right pad with
 * spaces if the logger name is less than 20 characters long.
 * </tr>
 *
 * <tr>
 * <td align=center>%.30c</td>
 * <td align=center>NA</td>
 * <td align=center>none</td>
 * <td align=center>30</td>
 *
 * <td>Truncate from the beginning if the logger name is longer than 30
 * characters.
 * </tr>
 *
 * <tr>
 * <td align=center>%20.30c</td>
 * <td align=center>false</td>
 * <td align=center>20</td>
 * <td align=center>30</td>
 *
 * <td>Left pad with spaces if the logger name is shorter than 20
 * characters. However, if logger name is longer than 30 characters,
 * then truncate from the beginning.
 * </tr>
 *
 * <tr>
 * <td align=center>%-20.30c</td>
 * <td align=center>true</td>
 * <td align=center>20</td>
 * <td align=center>30</td>
 *
 * <td>Right pad with spaces if the logger name is shorter than 20
 * characters. However, if logger name is longer than 30 characters,
 * then truncate from the beginning.
 * </tr>
 *
 * </table>
 *
 * <p>Below are some examples of conversion patterns.
 *
 * <dl>
 *
 * <p><dt><b>"%r [%t] %-5p %c %x - %m%n"</b>
 * <p><dd>This is essentially the TTCC layout.
 *
 * <p><dt><b>"%-6r [%15.15t] %-5p %30.30c %x - %m%n"</b>
 *
 * <p><dd>Similar to the TTCC layout except that the relative time is
 * right padded if less than 6 digits, thread name is right padded if
 * less than 15 characters and truncated if longer and the logger
 * name is left padded if shorter than 30 characters and truncated if
 * longer.
 *
 * </dl>
 *
 * <p>The above text is largely inspired from Peter A. Darnell and
 * Philip E. Margolis' highly recommended book "C -- a Software
 * Engineering Approach", ISBN 0-387-97389-3.
 */
class LOG4CPLUS_EXPORT PatternLayout : public Layout
{
public:
    // Ctors and dtor
    PatternLayout(const log4cplus::tstring &pattern);
    PatternLayout(const log4cplus::helpers::Properties &properties);
    virtual ~PatternLayout();

    virtual void formatAndAppend(log4cplus::tostream &output,
                                 const log4cplus::spi::InternalLoggingEvent &event);

protected:
    void init(const log4cplus::tstring &pattern);

    // Data
    log4cplus::tstring pattern;
    std::vector<pattern::PatternConverter *> parsedPattern;

private:
    // Disallow copying of instances of this class
    PatternLayout(const PatternLayout &);
    PatternLayout &operator=(const PatternLayout &);
};



} // end namespace log4cplus

#endif // _LOG4CPLUS_LAYOUT_HEADER_

