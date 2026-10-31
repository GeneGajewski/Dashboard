# *Dashboard for Net Logger*

Dashboard for Net Logger is a fast and easy monitoring application for [NetLogger](https://www.netlogger.org) amateur radio nets.

This application is built using Embarcadero's [C++ Builder Community Edition](https://www.embarcadero.com/products/cbuilder/starter/),
which is free to use for non-commercial purposes. I chose this toolset as I am a longtime user of C++ Builder and I appreciate the simplicity
of the C++ Builder/Delphi runtime library ecosystem for building native desktop apps.
Besides, I've been around since the [Turbo C 1.5](https://en.wikipedia.org/wiki/Borland_Turbo_C) days.

This is a straightforward IDE project in c++ using the Delphi VCL component library. There's no makefiles to deal with. It's themed as well with plenty of light and dark UI styles to choose from. It has a FireDAC SQLite backend which isn't really being needed/exploited at the moment, but will make it super easy to add advanced features in the future, such bulk storage and querying and so on, but the primary goal here is to be exceedingly *simple*, self explanatory and *easy on the eyes* - less distraction, more ***radio***!

New program updates can be queried for within the program and can be downloaded and installed if desired.

Dashboard is a fine example of what you can do as a ham radio hobby project where you're just kickin' back and enjoying yourself.



## AI Summary

# Purpose

A Windows VCL application that tracks amateur radio net checkins and displays them in a data grid, with features for browsing active and past nets.

# Key Features

## Data Management:

- Pulls checkin data from a REST API (https://www.netlogger.org/api)
- Displays results in a FireDAC memory table with a DBGrid UI
- Exports grid data to CSV files
- Sorts data by clicking column headers



## Display:

* Shows active or past radio nets with details (frequency, band, mode, net control, logger name)
* Updates via configurable poll rate (20-180 seconds)
* Shows a real-time clock with date/time (12/24-hour and UTC options)
* Highlights the "pointer" record in green
* Auto-fits column widths to content

## User Interface:

* Window state/preferences saved to Windows Registry
* About box and preferences dialog
* Column visibility/width/ordering persistence
* Multiple themes support
* Built-in help file (DASHBOARD.CHM)

## Utilities:

* Double-click callsign to open QRZ.com lookup
* Automatic update checking from remote server
* Logging via CodeSite
* XML parsing for checkin responses
* File export with sanitized filenames

## Architecture:

* Uses Delphi/C++ Builder VCL framework
* External library: TLabeledDBGrid from Ethea (DbAware Labeled Components)
* Async REST requests with completion handlers
* Event-driven timers for refresh and clock updates

[WG5ENE](https://qrz.com/db/wg5ene)

