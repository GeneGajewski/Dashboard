<?php
/*
    This file is part of GUP.

    GUP is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GUP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with GUP.  If not, see <http://www.gnu.org/licenses/>.
*/



$DLURL = "https://www.gajewski.net/update/Dashboard.1.0.0.msi";

$major = $_GET["maj"]; 
$minor = $_GET["min"]; 
$release = $_GET["rel"]; 
$build = $_GET["bld"]; 

$Ver = array( 1, 0, 0, 0);
$VersionStr = "0.9.0.0"; // X.Y.Z

$Info = "This is Dashboard version 1.0";

$major = (int) $major;
$minor = (int) $minor;
$release = (int) $release;
$build = (int) $build;

if ( $Ver[0] <= $major and $Ver[1] <= $minor and $Ver[2] <= $release and $Ver[3] <= $build)
	echo 
"<?xml version=\"1.0\"?>
<GUP>
	<NeedToBeUpdated>no</NeedToBeUpdated>
</GUP>
";

else

	echo 
"<?xml version=\"1.0\"?>
<GUP>
	<NeedToBeUpdated>yes</NeedToBeUpdated>
	<Version>$VersionStr</Version>
	<Location>$DLURL</Location>
	<Info>$Info</Info>
</GUP>";


?>

