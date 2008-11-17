/*
 * $Id$
 */

package org.opendds.jms.transport.spi;

import org.opendds.jms.common.SvcConfDirective;

/**
 * @author  Steven Stallion
 * @version $Revision$
 */
public interface Transport {

    String getName();

    Class getConfigurationClass();

    SvcConfDirective getDirective();
}
