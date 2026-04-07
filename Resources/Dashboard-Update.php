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

// Get a 64-bit integer, MS style - easier to just simply compare versions that way

function bigNum($maj, $min, $rel, $bld) {
	$result   = ((int)$maj) << 48;
	$result  |= ((int)$min) << 32;
	$result  |= ((int)$rel) << 16;
	$result  |= ((int)$bld);

	return $result;
}    

$DLURL = "https://www.gajewski.net/update/Dashboard Installer.exe";

$major   = $_GET["maj"]; 
$minor   = $_GET["min"]; 
$release = $_GET["rel"]; 
$build   = $_GET["bld"]; 

$VersionStr = "1.2.0.0"; 


$Info = "This is Dashboard version 1.2.0.0

Minor cosmetic and program changes. 
CHM-based help file - not really needed 
but why not.

 WG5ENE
";

$major = (int) $major;
$minor = (int) $minor;
$release = (int) $release;
$build = (int) $build;

if ( bigNum(1,2,0,0) <= bigNum ($major, $minor, $release, $build))
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

